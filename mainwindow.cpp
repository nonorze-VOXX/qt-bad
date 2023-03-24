#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(bulr()));
    ui->speedSlider->setRange(0,100);

    QPixmap dark = QPixmap("../micro/bulb_dark.png");
    ui->label_1->setPixmap(dark);
    ui->label_2->setPixmap(dark);
    ui->label_3->setPixmap(dark);
    ui->label_4->setPixmap(dark);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void changeBulb(QLabel *label,int arg1){

    QPixmap pixmap = QPixmap("../micro/bulb_light.png");

    QPixmap dark = QPixmap("../micro/bulb_dark.png");
    if(arg1!=0){
        //ui->label_1->setPixmap(pixmap);
        label->setPixmap(pixmap);
    }else{
        label->setPixmap(dark);

    }
}
void MainWindow::on_checkBox_stateChanged(int arg1)
{
//    changeBulb(ui->label_1,arg1);
}


void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
//changeBulb(ui->label_2,arg1);
}


void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
//changeBulb(ui->label_3,arg1);
}


void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
//changeBulb(ui->label_4,arg1);
}

void MainWindow::bulr(){
    counter=counter- 1;
    if(counter<=0){
        timer->stop();
    }else{
        //timer->start(1000);
    }
    Qt::CheckState t = Qt::CheckState(1);
    Qt::CheckState f = Qt::CheckState(0);

    if(counter%2==0){

        changeBulb(ui->label_1,1);
        changeBulb(ui->label_2,1);
        changeBulb(ui->label_3,0);
        changeBulb(ui->label_4,0);

        ui->checkBox->setCheckState(t);
        ui->checkBox_2->setCheckState(t);
        ui->checkBox_3->setCheckState(f);
        ui->checkBox_4->setCheckState(f);

    }else{

        changeBulb(ui->label_1,0);
        changeBulb(ui->label_2,0);
        changeBulb(ui->label_3,1);
        changeBulb(ui->label_4,1);

        ui->checkBox->setCheckState(f);
        ui->checkBox_2->setCheckState(f);
        ui->checkBox_3->setCheckState(t);
        ui->checkBox_4->setCheckState(t);
    }

}

void MainWindow::on_shining_clicked()
{
    int check1 = ui->checkBox->checkState();
    changeBulb(ui->label_1,check1);
    int check2 = ui->checkBox_2->checkState();
    changeBulb(ui->label_2,check2);
    int check3 = ui->checkBox_3->checkState();
    changeBulb(ui->label_3,check3);
    int check4 = ui->checkBox_4->checkState();
    changeBulb(ui->label_4,check4);

}


void MainWindow::on_dump_clicked()
{

//    changeBulb(ui->label_1,1);
//    changeBulb(ui->label_2,1);
//    changeBulb(ui->label_3,0);
//    changeBulb(ui->label_4,0);
//    Qt::CheckState t = Qt::CheckState(1);
//    Qt::CheckState f = Qt::CheckState(0);

//    ui->checkBox->setCheckState(t);
//    ui->checkBox_2->setCheckState(t);
//    ui->checkBox_3->setCheckState(f);
//    ui->checkBox_4->setCheckState(f);

    int target = ui->spinBox->value();
    counter =target*2;

        timer->start(ShiningSpeed+1);//avoid 0 case

}




void MainWindow::changeSwitchSpeed(int speed)
{
    QString s = ">=100";
    if(speed<=0){
        s = "<=0";
    }else
    if(speed<50){
        s = "<50";
    }else if(speed<100){
        s = "<100";
    }
    ui->cout->setText(s);
    ui->speedBar->setValue(speed);
    ShiningSpeed = speed*5;
}

void MainWindow::on_speedBar_valueChanged(int value)
{
   changeSwitchSpeed(value);
}


void MainWindow::on_speedSlider_sliderMoved(int position)
{
    changeSwitchSpeed(position);

}


void MainWindow::on_pushButton_clicked()
{
    timer->stop();
}
