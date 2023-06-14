#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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
    void QTEChange();
    void on_button1_pressed();
    void on_button2_pressed();
    void on_button3_pressed();
    void on_button4_pressed();
    void buttonClick(int b);
private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer();
    bool flag;
    void scoreChange(int s);
};
#endif // MAINWINDOW_H
