#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

#define MAJOR_NUM 61
#define MODULE_NAME "lab6-2"

#define CHRDEVBASE_MAJOR 200
#define  CHRDEBBASE_NAME "chrdevbase"

static int iCount = 0;
static char userChar[100];


int gpio_export(unsigned int gpio) {
  int len;
  struct file* fd;
  loff_t pos=0;
  mm_segment_t old_fs;
  char buf[64];
  old_fs=get_fs();
  set_fs(get_ds());

  fd = filp_open("/sys/class/gpio/export", O_WRONLY,0);
  len = snprintf(buf, sizeof(buf), "%d", gpio);
  vfs_write(fd, buf, 3,&pos);
  filp_close(fd,NULL);
  set_fs(old_fs);

  return 0;
}

int gpio_unexport(unsigned int gpio) {
  int len;
  struct file* fd;
  loff_t pos=0;
  mm_segment_t old_fs;
  char buf[64];
  old_fs=get_fs();
  set_fs(get_ds());

  fd = filp_open("/sys/class/gpio/unexprot", O_WRONLY,0);
  if (fd < 0) {
    // perror("gpio/export");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%d", gpio);
  vfs_write(fd, buf, len,&pos);
  filp_close(fd,NULL);
  set_fs(old_fs);
  return 0;
}

int gpio_set_dir(unsigned int gpio, int status) {
  struct file* fd;
  loff_t pos=0;
  mm_segment_t old_fs;
  char buf[64]="/sys/class/gpio/gpio000/direction\0";
  char buf1[64]="out";
  buf[20]=gpio/100+'0';
  buf[21]=(gpio%100/10)+'0';
  buf[22]=(gpio%10)+'0';
  printk("%s\n",buf);

  old_fs=get_fs();
  set_fs(get_ds());

  // snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", gpio);

  fd = filp_open(buf, O_WRONLY,0);
  if (status == 1) {
    vfs_write(fd, buf1,strlen(buf1) ,&pos);
  } else {
    vfs_write(fd, "in", 2,&pos);
  }
  filp_close(fd,NULL);
  set_fs(old_fs);
  return 0;
}

int gpio_set_value(unsigned int gpio, int value) {
  struct file* fd;
  loff_t pos=0;
  mm_segment_t old_fs;

  char buf[64]="/sys/class/gpio/gpio000/value";
  buf[20]=gpio/100+'0';
  buf[21]=(gpio%100/10)+'0';
  buf[22]=(gpio%10)+'0';
//  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

  old_fs=get_fs();
  set_fs(get_ds());
  fd = filp_open(buf, O_WRONLY,0);
  if (value == 0) {
    vfs_write(fd, "0\0", 2,&pos);
  } else {
    vfs_write(fd, "1\0", 2,&pos);
  }
  filp_close(fd,NULL);
  set_fs(old_fs);
  return 0;
}
int gpio_read_value(unsigned int gpio) {
  struct file* fd;
  loff_t pos=0;
  mm_segment_t old_fs;

  char buf[64]="/sys/class/gpio/gpio000/value";
  char buf1[64]="";
  buf[20]=gpio/100+'0';
  buf[21]=(gpio%100/10)+'0';
  buf[22]=(gpio%10)+'0';
//  snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", gpio);

  old_fs=get_fs();
  set_fs(get_ds());
  fd = filp_open(buf, O_WRONLY,0);
  vfs_read(fd,buf1, 2,&pos);
  filp_close(fd,NULL);
  set_fs(old_fs);

  return buf1[0]-'0';
}


static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
    printk("Read:Enter Read function\n");
    //printk("W_buf_size: %d\n", (int)count);
    printk("%d\n", 1);
    __copy_from_user(userChar, buf, count);
    printk("%d\n", 1);
    int ledCode = (userChar[0]-'0')*100+(userChar[1]-'0')*10+(userChar[2]-'0');
    printk("%d\n", 1);
    int v=gpio_read_value(ledCode);
    printk("%d\n", 1);
    char buf1[64];
    buf[0]=v+'0';
    buf[1]='\0';

    printk("%d\n", 1);
    __copy_to_user (buf,userChar, 2);
    // int powerCode = userChar[4]-'0';
    // printk("write: %d %d\n", ledCode, powerCode);
    // gpio_export(ledCode);
    // gpio_set_dir(ledCode, 1);
    // gpio_set_value(ledCode, powerCode);
    // printk("device read\n");
    return count;
};

static ssize_t drv_write(struct file *filp,const char *buf, size_t count, loff_t *ppos)
{
    printk("Write:Ener Write function\n");
    //printk("W_buf_size: %d\n", (int)count);
    //raw_copy_from_user(userChar, buf, count);
    __copy_from_user(userChar, buf, count);
    int ledCode = (userChar[0]-'0')*100+(userChar[1]-'0')*10+(userChar[2]-'0');
    int powerCode = userChar[4]-'0';
    printk("write: %d %d\n", ledCode, powerCode);
    gpio_export(ledCode);
    gpio_set_dir(ledCode, 1);
    gpio_set_value(ledCode, powerCode);

    iCount++;
    return count;
};

long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("I/O Control:Enter I/O Control function\n");
    return 0;
};

static int drv_open(struct inode *inode, struct file *filp)
{
    printk("Open:Enter Open function\n");
    return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{
    printk("Release:Enter Release function\n");
    return 0;
}


struct file_operations drv_fops = 
{
    .owner= THIS_MODULE,
    .read= drv_read,
    .write= drv_write, 
    .unlocked_ioctl= drv_ioctl,
    .open= drv_open,
    .release= drv_release,
};

static int demo_init(void)
{
    if (register_chrdev(MAJOR_NUM, "lab6-2", &drv_fops) < 0) {
        printk("<1>%s: can't get major %d\n", MODULE_NAME, MAJOR_NUM);
        return (-EBUSY);
    }
    printk(KERN_INFO "<1>%s: started\n", MODULE_NAME);
    return 0;
}
static void demo_exit(void)
{
    unregister_chrdev(MAJOR_NUM, "lab6-2");
    printk("<1>%s: removed\n", MODULE_NAME);
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");