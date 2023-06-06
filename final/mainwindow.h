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
    void on_button1_toggled(bool checked);
    void QTEChange();
    void on_button2_toggled(bool checked);

    void on_button3_toggled(bool checked);

    void on_button4_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QTimer *timer = new QTimer();
};
#endif // MAINWINDOW_H
