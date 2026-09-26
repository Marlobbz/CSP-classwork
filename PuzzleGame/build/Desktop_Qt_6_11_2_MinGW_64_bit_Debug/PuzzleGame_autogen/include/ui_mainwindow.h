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
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout;
    QWidget *puzzleWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_2;
    QPushButton *puzzleButton5;
    QPushButton *puzzleButton2;
    QPushButton *puzzleButton1;
    QPushButton *puzzleButton8;
    QPushButton *puzzleButton6;
    QPushButton *puzzleButton3;
    QPushButton *puzzleButton0;
    QPushButton *puzzleButton4;
    QPushButton *puzzleButton7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(961, 713);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        puzzleWidget = new QWidget(centralwidget);
        puzzleWidget->setObjectName("puzzleWidget");
        layoutWidget = new QWidget(puzzleWidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(80, 10, 784, 623));
        gridLayout_2 = new QGridLayout(layoutWidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        puzzleButton5 = new QPushButton(layoutWidget);
        puzzleButton5->setObjectName("puzzleButton5");
        puzzleButton5->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton5, 1, 2, 1, 1);

        puzzleButton2 = new QPushButton(layoutWidget);
        puzzleButton2->setObjectName("puzzleButton2");
        puzzleButton2->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton2, 0, 2, 1, 1);

        puzzleButton1 = new QPushButton(layoutWidget);
        puzzleButton1->setObjectName("puzzleButton1");
        puzzleButton1->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton1, 0, 1, 1, 1);

        puzzleButton8 = new QPushButton(layoutWidget);
        puzzleButton8->setObjectName("puzzleButton8");
        puzzleButton8->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton8, 2, 2, 1, 1);

        puzzleButton6 = new QPushButton(layoutWidget);
        puzzleButton6->setObjectName("puzzleButton6");
        puzzleButton6->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton6, 2, 0, 1, 1);

        puzzleButton3 = new QPushButton(layoutWidget);
        puzzleButton3->setObjectName("puzzleButton3");
        puzzleButton3->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton3, 1, 0, 1, 1);

        puzzleButton0 = new QPushButton(layoutWidget);
        puzzleButton0->setObjectName("puzzleButton0");
        puzzleButton0->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton0, 0, 0, 1, 1);

        puzzleButton4 = new QPushButton(layoutWidget);
        puzzleButton4->setObjectName("puzzleButton4");
        puzzleButton4->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton4, 1, 1, 1, 1);

        puzzleButton7 = new QPushButton(layoutWidget);
        puzzleButton7->setObjectName("puzzleButton7");
        puzzleButton7->setMinimumSize(QSize(150, 150));

        gridLayout_2->addWidget(puzzleButton7, 2, 1, 1, 1);


        gridLayout->addWidget(puzzleWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 961, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\213\274\345\233\276\346\270\270\346\210\217", nullptr));
        puzzleButton5->setText(QString());
        puzzleButton2->setText(QString());
        puzzleButton1->setText(QString());
        puzzleButton8->setText(QString());
        puzzleButton6->setText(QString());
        puzzleButton3->setText(QString());
        puzzleButton0->setText(QString());
        puzzleButton4->setText(QString());
        puzzleButton7->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
