#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    std::map<std::string, int> led = {
        {"LED1", 466},
        {"LED2", 396},
        {"LED3", 429},
        {"LED4", 398},
    };
    std::map<std::string, int> power = {{"on", 1}, {"off", 0}};

    int ledCode = led[argv[1]];
    if(argc==2){
        //read
        char buf[1024];
        int gpio=ledCode;
        snprintf(buf, sizeof(buf), "%d", gpio);
        FILE *fp = fopen("/dev/lab6-2", "w+");
        if (fp == NULL) {
            printf("can't open device\n");
            return 0;
        }
        fwrite(buf, sizeof(buf), 1, fp);
        fread(buf, 1, 1, fp);
        printf("%d %c\n",gpio,buf[0]);
        fclose(fp);
    }
    else{
        //write
        int powerCode = power[argv[2]];
        char buf[1024];
        // for (int i=0;i<4;i++){
            int gpio=ledCode;
            snprintf(buf, sizeof(buf), "%d %d", gpio,powerCode);
            printf("%s\n",buf);
            FILE *fp = fopen("/dev/lab6-2", "w+");
            if (fp == NULL) {
                printf("can't open device\n");
                return 0;
            }
            fwrite(buf, sizeof(buf), 1, fp);
            fclose(fp);
        // }

    }
    return 0;
}