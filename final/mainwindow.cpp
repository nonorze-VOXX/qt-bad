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
#include <cmath>

char  GPIOPath[] = "/sys/class/gpio/\0";
int map[4] = { 255, 398, 392 ,481};
//255 - > 15
//398 - > 29
//392 - > 12
//481 - > 18
int gpio_state[4] = {0,0,0,0};
//char  GPIOPath[] = "/home/green-ridkr/code/university/qt-bad/final/\0";
int score = 0;
int gpio_set_value(unsigned int gpio, int value) {
    int fd;
    char buf[64];

    char setDirExportPath[1024] ="";
    strcpy(setDirExportPath, GPIOPath);
    char str[1024] = "";
    snprintf(str, sizeof(str), "gpio%d/value", gpio);
    strcat(setDirExportPath,str);

    strcpy(buf, setDirExportPath);

    printf("%d: %d :%s\n",gpio,value,buf);
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
void outputScore(int score){
    int fd = open("./score", O_WRONLY);
    if (fd < 0) {
        perror("score file not found");
    }

    write(fd, std::to_string(score).c_str(),(int)log10(score)+1) ;
    close(fd);
}
void MainWindow::QTEChange(){
    if(flag){
        flag = false;
    }else{
        scoreChange(0);
    }
    int qteIndex = (int)random()% 4;
    if(gpio_state[qteIndex]==1){
        qteIndex+=1;
        qteIndex%=4;
    }
    for(int i=0;i<4;i++){
        if(i==qteIndex){
            gpio_state[i]=1;
            gpio_set_value(map[i], 1);
            ui->pixmap->setGeometry(QRect(40 + 166 * i,300,300,300));
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
        gpio_set_value(map[var],0);
    }
    ui->label->setText(QString("score"));

    //timer->setSingleShot(true);
    timer->start(3000);
    flag = false;

    QPixmap pixmap = QPixmap("../final/bulb.jpg");
    ui->pixmap->setPixmap(pixmap);
    ui->pixmap->setGeometry(QRect(40,300,0,0));  // make it disapear
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClick(int b){
    flag = true;
    if(gpio_state[b]){
        timer->start(3000);
        QTEChange();
        scoreChange(score+1);
    }else{
        scoreChange(0);
    }
}
void MainWindow::scoreChange(int s){
    score = s;
    outputScore(score);
    QString o = QStringLiteral("%1. ").arg(score);
    ui->label->setText(o);
}

void MainWindow::on_button1_pressed()
{
    buttonClick(0);
}

void MainWindow::on_button2_pressed()
{
    buttonClick(1);
}

void MainWindow::on_button3_pressed()
{
    buttonClick(2);
}

void MainWindow::on_button4_pressed()
{
    buttonClick(3);
}

