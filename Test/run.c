#include <stdio.h>

int main(int arg,char *args)
{
    char buf[1024] = "Data Input 123456 hello world\n";
    FILE *fp = fopen("/dev/lab6-2", "w+");
    if (fp == NULL) {
        printf("can't open device\n");
        return 0;
    }
    fwrite(buf, sizeof(buf), 1, fp);
    fread(buf, sizeof(buf), 1, fp);
    fclose(fp);
    return 0;
}