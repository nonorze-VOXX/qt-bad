#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUM 61
#define MODULE_NAME "lab6-2"

#define CHRDEVBASE_MAJOR 200
#define  CHRDEBBASE_NAME "chrdevbase"

static int iCount = 0;
static char userChar[100];

static void demo_exit(void)
{
    unregister_chrdev(MAJOR_NUM, "lab6-2");
    printk("<1>%s: removed\n", MODULE_NAME);
}

static ssize_t drv_read(struct file *filp, char *buf, size_t count, loff_t *ppos)
{
    printk("device read\n");
    return count;
};

static ssize_t drv_write(struct file *filp,const char *buf, size_t count, loff_t *ppos)
{
    printk("device write\n");
    printk("W_buf_size: %d\n", (int)count);
    //raw_copy_from_user(userChar, buf, count);
    __copy_from_user(userChar, buf, count);
    userChar[count - 1] = 0;
    printk("userChar: %d\n", (int)sizeof(userChar));

    iCount++;
    return count;
};

long drv_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    printk("device ioctl\n");
    return 0;
};

static int drv_open(struct inode *inode, struct file *filp)
{
    printk("device open\n");
    return 0;
}

static int drv_release(struct inode *inode, struct file *filp)
{
    printk("device close\n");
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

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");
