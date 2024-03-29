#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qlabel.h>
#include<QTimer>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_checkBox_stateChanged(int arg1);


    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);

    void on_shining_clicked();
    void bulr();
    void on_dump_clicked();

    void changeSwitchSpeed(int speed);


    void on_speedBar_valueChanged(int value);

    void on_speedSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QTimer *timer=new QTimer() ;
    int counter = 0;
    int ShiningSpeed = 1;
};
#endif // MAINWINDOW_H
