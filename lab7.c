#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>

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
        led[i] = 1-led[i];
    }
    char* str = (char*)data;
    printf("%s\n",str);

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
            pthread_create(&t, NULL, child, "child");
            pthread_join(t, NULL);
        }
        printf("%s\n","parent");
    }else{
        printf("amogus\n");
    }
    
    return 0;

}