/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
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
    QLineEdit *lineEdit;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn9;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn6;
    QPushButton *btn8;
    QPushButton *btn0;
    QPushButton *btn3;
    QPushButton *btn7;
    QPushButton *btnDot;
    QPushButton *btnEqual;
    QPushButton *btnDiv;
    QPushButton *btnMul;
    QPushButton *btnSub;
    QPushButton *btnAdd;
    QPushButton *btnClear;
    QPushButton *btnBackspace;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(70, 20, 451, 91));
        btn1 = new QPushButton(centralwidget);
        btn1->setObjectName("btn1");
        btn1->setGeometry(QRect(30, 320, 99, 81));
        btn2 = new QPushButton(centralwidget);
        btn2->setObjectName("btn2");
        btn2->setGeometry(QRect(140, 320, 99, 81));
        btn9 = new QPushButton(centralwidget);
        btn9->setObjectName("btn9");
        btn9->setGeometry(QRect(250, 140, 99, 81));
        btn4 = new QPushButton(centralwidget);
        btn4->setObjectName("btn4");
        btn4->setGeometry(QRect(30, 230, 99, 81));
        btn5 = new QPushButton(centralwidget);
        btn5->setObjectName("btn5");
        btn5->setGeometry(QRect(140, 230, 99, 81));
        btn6 = new QPushButton(centralwidget);
        btn6->setObjectName("btn6");
        btn6->setGeometry(QRect(250, 230, 99, 81));
        btn8 = new QPushButton(centralwidget);
        btn8->setObjectName("btn8");
        btn8->setGeometry(QRect(140, 140, 99, 81));
        btn0 = new QPushButton(centralwidget);
        btn0->setObjectName("btn0");
        btn0->setGeometry(QRect(30, 420, 99, 81));
        btn3 = new QPushButton(centralwidget);
        btn3->setObjectName("btn3");
        btn3->setGeometry(QRect(250, 320, 99, 81));
        btn7 = new QPushButton(centralwidget);
        btn7->setObjectName("btn7");
        btn7->setGeometry(QRect(30, 140, 99, 81));
        btnDot = new QPushButton(centralwidget);
        btnDot->setObjectName("btnDot");
        btnDot->setGeometry(QRect(140, 420, 99, 81));
        btnEqual = new QPushButton(centralwidget);
        btnEqual->setObjectName("btnEqual");
        btnEqual->setGeometry(QRect(250, 420, 99, 81));
        btnDiv = new QPushButton(centralwidget);
        btnDiv->setObjectName("btnDiv");
        btnDiv->setGeometry(QRect(360, 140, 99, 81));
        btnMul = new QPushButton(centralwidget);
        btnMul->setObjectName("btnMul");
        btnMul->setGeometry(QRect(360, 230, 99, 81));
        btnSub = new QPushButton(centralwidget);
        btnSub->setObjectName("btnSub");
        btnSub->setGeometry(QRect(360, 320, 99, 81));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");
        btnAdd->setGeometry(QRect(360, 420, 99, 81));
        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");
        btnClear->setGeometry(QRect(470, 320, 99, 81));
        btnBackspace = new QPushButton(centralwidget);
        btnBackspace->setObjectName("btnBackspace");
        btnBackspace->setGeometry(QRect(470, 140, 99, 171));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnDot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btnEqual->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        btnDiv->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        btnSub->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btnBackspace->setText(QCoreApplication::translate("MainWindow", "Backspace", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
