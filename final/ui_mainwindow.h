/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QLabel *label;
    QLabel *pixmap;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        button1 = new QPushButton(centralwidget);
        button1->setObjectName(QStringLiteral("button1"));
        button1->setGeometry(QRect(70, 250, 80, 25));
        button2 = new QPushButton(centralwidget);
        button2->setObjectName(QStringLiteral("button2"));
        button2->setGeometry(QRect(250, 250, 80, 25));
        button3 = new QPushButton(centralwidget);
        button3->setObjectName(QStringLiteral("button3"));
        button3->setGeometry(QRect(420, 250, 80, 25));
        button4 = new QPushButton(centralwidget);
        button4->setObjectName(QStringLiteral("button4"));
        button4->setGeometry(QRect(580, 250, 80, 25));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(280, 110, 66, 18));
        pixmap = new QLabel(centralwidget);
        pixmap->setObjectName(QStringLiteral("pixmap"));
        pixmap->setGeometry(QRect(30, 290, 171, 231));
        pixmap->setPixmap(QPixmap(QString::fromUtf8("bulb.jpg")));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        button1->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        button1->setShortcut(QApplication::translate("MainWindow", "Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        button2->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        button2->setShortcut(QApplication::translate("MainWindow", "W", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        button3->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        button3->setShortcut(QApplication::translate("MainWindow", "E", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        button4->setText(QApplication::translate("MainWindow", "PushButton", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        button4->setShortcut(QApplication::translate("MainWindow", "R", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
