#include <ctime>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <iterator>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// char  GPIOPath[] = "/sys/class/gpio/\0";
char  GPIOPath[] = "./";


int gpio_export(unsigned int gpio){
    int fd, len;
    char buf[64]="";
    
    char exportPath[1024] ="";
    strcpy(exportPath, GPIOPath);
    char exportStr[] = "export";
    strcat(exportPath,exportStr);
    
    fd = open(exportPath, O_WRONLY);
    if(fd<0){
        perror("gpio/export");
        return fd;
    }
    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

int gpio_unexport(unsigned int gpio) {
  int fd, len;
  char buf[64]="";

    char unexportPath[1024] ="";
    strcpy(unexportPath, GPIOPath);
    char unexportStr[] = "unexport";
    strcat(unexportPath,unexportStr);

  fd = open(unexportPath, O_WRONLY);
  if (fd < 0) {
    perror("gpio/unexport");
    return fd;
  }

  len = snprintf(buf, sizeof(buf), "%d", gpio);
  write(fd, buf, len);
  close(fd);
  return 0;
}
int gpio_set_dir(unsigned int gpio, std::string dirStatus) {
  int fd;
  char buf[64]="";
  printf("%d\n",gpio);

    char setDirExportPath[1024] ="";
    strcpy(setDirExportPath, GPIOPath);
    char str[1024] = "";
    snprintf(str, sizeof(str), "%d/direction", gpio);
    strcat(setDirExportPath,str);
    
    strcpy(buf, setDirExportPath);
    
  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("gpio/direction");
    return fd;
  }
  if (dirStatus == "out") {
    write(fd, "out", 4);
  } else {
    write(fd, "in", 3);
  }
  close(fd);
  return 0;
}

int gpio_set_value(unsigned int gpio, int value) {
  int fd;
  char buf[64];

    char setDirExportPath[1024] ="";
    strcpy(setDirExportPath, GPIOPath);
    char str[1024] = "";
    snprintf(str, sizeof(str), "/gpio%d/value", gpio);
    strcat(setDirExportPath,str);
    
    strcpy(buf, setDirExportPath);

  fd = open(buf, O_WRONLY);
  if (fd < 0) {
    perror("gpio/set-value");
    return fd;
  }
  if (value == 0) {
    write(fd, "0", 2);
  } else {
    write(fd, "1", 2);
  }
  close(fd);
  return 0;
}

// int main(int argc, char *argv[]) {
//   std::map<std::string, int> led = {
//       {"LED1", 255},
//       {"LED2", 396},
//       {"LED3", 429},
//       {"LED4", 398},
//   };
//   std::map<std::string, int> power = {{"on", 1}, {"off", 0}};

// if(argc==3){
//     int gpio  =0;
//     int value = 0;
//     if(sizeof(argv[1])>1){
//         gpio = led[argv[1]];
//     }else{
//         gpio = atoi(argv[1]);
//     }
//     if(sizeof(argv[2])>1){
//         value = power[argv[2]];
//     }else{
//         value = atoi(argv[2]);
//     }
//     std::cout<<gpio<<std::endl;
//     std::cout<<value<<std::endl;
//     gpio_set_value(gpio, value);
// }else{
//     std::cout<<"arg num error"<<std::endl;
// }



//   return 0;
// }
pthread_mutex_t mutex;
int led[4]= {0,0,0,0};

void* child(void* data){
    pthread_mutex_lock(&mutex);
    
    printf("status:");
    for(int i = 0;i<4;i++){
        printf("%d",led[i]);
    }
    printf("\n");
    for(int i = 0;i<4;i++){
        printf("GPIO:%d  status:%d\n",i,led[i]);
        int map[4] = { 255, 396, 429, 398};
        gpio_set_value(map[i], led[i]);
        led[i] = 1-led[i];
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);

}

int main(int argc, char *argv[]) {

    if(argc == 3){
        char* s = argv[1];
        for(int i = 0;i<4;i++){
            if(s[i]=='0'){
                led[i]=0;
            }else{
                led[i]=1;
            }
        }
        int times = atoi(argv[2]);
        for (int i = 0 ;i<times;i++){
            pthread_t t;
            pthread_create(&t, NULL, child, NULL);
            pthread_join(t, NULL);
        }
        printf("%s\n","parent");
    }else{
        printf("amogus\n");
    }
    
    return 0;

}