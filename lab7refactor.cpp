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
#include "unistd.h"
#include <semaphore.h>

char  GPIOPath[] = "/sys/class/gpio/\0";
int map[4] = { 429, 398, 396 ,466};
// char  GPIOPath[] = "./";


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
    snprintf(str, sizeof(str), "gpio%d/direction", gpio);
    strcat(setDirExportPath,str);
    
    strcpy(buf, setDirExportPath);
    // printf("%s\n",setDirExportPath);
    
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

sem_t sem;
pthread_mutex_t mutex;
int sem_times=0;

int led[4]= {0,0,0,0};

void* childSem(void* data){
      sem_wait(&sem);
      printf("status:");
      for(int i = 0;i<4;i++){
          printf("%d",led[i]);
      }
      printf("\n");
      for(int i = 0;i<4;i++){
          printf("GPIO:%d  status:%d\n",i,led[i]);
          gpio_set_value(map[i], led[i]);
          led[i] = 1-led[i];
      }
      sleep(1);
      sem_post(&sem);

    pthread_exit(NULL);
}


void* child(void* data){
    pthread_mutex_lock(&mutex);
    
    printf("status:");
    for(int i = 0;i<4;i++){
        printf("%d",led[i]);
    }
    printf("\n");
    for(int i = 0;i<4;i++){
        printf("GPIO:%d  status:%d\n",i,led[i]);
        gpio_set_value(map[i], led[i]);
        led[i] = 1-led[i];
    }
    sleep(1);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);

}

int main(int argc, char *argv[]) {
    sem_init(&sem, 0, 0);
      for(int i = 0; i<3;i++){
        gpio_export(map[i]);
        gpio_set_dir(map[i], "out");
      }
    if(argc == 4){
      if(atoi(argv[3])==0){
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
      }else{
        //sem
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
            pthread_create(&t, NULL, childSem, NULL);
            pthread_join(t, NULL);
        }
          sem_post(&sem);
      }
    }else{
        printf("amogus\n");
    }
    
    return 0;

}