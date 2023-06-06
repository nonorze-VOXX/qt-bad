#include "mainwindow.h"
#include "ui_mainwindow.h"
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

//char  GPIOPath[] = "/sys/class/gpio/\0";
int map[4] = { 429, 398, 396 ,466};
int gpio_state[4] = {0,0,0,0};
char  GPIOPath[] = "/home/green-rider/code/university/qt-bad/final/\0";
int gpio_set_value(unsigned int gpio, int value) {
    int fd;
    char buf[64];

    char setDirExportPath[1024] ="";
    strcpy(setDirExportPath, GPIOPath);
    char str[1024] = "";
    snprintf(str, sizeof(str), "gpio%d/value", gpio);
    strcat(setDirExportPath,str);

    strcpy(buf, setDirExportPath);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-value");
        perror(buf);
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
void MainWindow::QTEChange(){
    int qteIndex = (int)random()% 4;
    if(gpio_state[qteIndex]==1){
        qteIndex+=1;
        qteIndex%=4;
    }
    for(int i=0;i<4;i++){
        if(i==qteIndex){
            gpio_state[i]=1;
            gpio_set_value(map[i], 1);
        }else{
            gpio_state[i]=0;
            gpio_set_value(map[i], 0);
        }
    }
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(QTEChange()));
    for (int var = 0; var < 4; ++var) {
        gpio_set_value(map[var],1);
    }
    timer->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button1_toggled(bool checked)
{
    if(checked&&gpio_state[0]){
        QTEChange();
    }
}


void MainWindow::on_button2_toggled(bool checked)
{
    if(checked&&gpio_state[1]){
        QTEChange();
    }

}


void MainWindow::on_button3_toggled(bool checked)
{
    if(checked&&gpio_state[2]){
        QTEChange();
    }

}


void MainWindow::on_button4_toggled(bool checked)
{
    if(checked&&gpio_state[3]){
        QTEChange();
    }

}

