#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>
#include <bits/stdc++.h>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    buttons[0] = ui->puzzleButton0;
    buttons[1] = ui->puzzleButton1;
    buttons[2] = ui->puzzleButton2;
    buttons[3] = ui->puzzleButton3;
    buttons[4] = ui->puzzleButton4;
    buttons[5] = ui->puzzleButton5;
    buttons[6] = ui->puzzleButton6;
    buttons[7] = ui->puzzleButton7;
    buttons[8] = ui->puzzleButton8;

    for (int i=0;i<9;++i)//循环将按钮与点击函数连接
    {
        connect(buttons[i], &QPushButton::clicked,
                this, &MainWindow::puzzleButtonClicked);
    }

    // 原图是按正方形裁剪的，所以九宫格容器也改成正方形，避免拼好后被拉变形
    ui->layoutWidget->setGeometry(180, 20, 600, 600);
    // 去掉格子之间的间距和整体边距，9 块图才能真正连成一整张
    ui->gridLayout_2->setSpacing(0);
    ui->gridLayout_2->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 9; ++i) {
        //忽略按钮自身的 sizeHint，让它完全由布局拉满所在格子
        buttons[i]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        buttons[i]->setStyleSheet(
            "QPushButton{border:0px;padding:0px;margin:0px;background:transparent;}");
    }

    loadPuzzleImage();
    shufflePuzzle();
    refreshPuzzle();

    // 构造函数里布局尚未激活，按钮尺寸还不是最终值；
    // 等事件循环启动、布局生效后再按真实尺寸刷新一次
    QTimer::singleShot(0, this, [this]() { refreshPuzzle(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

//功能部分：
void MainWindow::loadPuzzleImage()
{
    QPixmap image(":/image/test.png");

    if (image.isNull()) {
        return;
    }

    int size = qMin(image.width(), image.height());

    image = image.copy((image.width()-size)/2,(image.height()-size)/2,size,size);

    int pieceSize = size / 3;
    for(int i=0;i<9;i++)
    {
        int row=i/3;
        int col=i%3;
        QPixmap piece=image.copy(col*pieceSize,row*pieceSize,pieceSize,pieceSize);
        puzzleImages[i]=piece;
        puzzleState[i]=i;
    }
}

void MainWindow::shufflePuzzle()
{
    vector<int> temp={0,1,2,3,4,5,6,7,8};
    random_device rd;
    mt19937 g(rd());
    shuffle(temp.begin(),temp.end(),g);

    for(int i=0;i<9;i++)
    {
        puzzleState[i]=temp[i];
    }
}

void MainWindow::refreshPuzzle()
{
    for(int i=0;i<9;i++)
    {
        const QSize target = buttons[i]->size();
        if(target.isEmpty()) continue;
        //按按钮的真实尺寸缩放拼图块
        buttons[i]->setIcon(QIcon(puzzleImages[puzzleState[i]].scaled(target, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        buttons[i]->setIconSize(target);
    }
}

//交换部分：
void MainWindow::puzzleButtonClicked()//点击函数
{
    QPushButton *button=qobject_cast<QPushButton*>(sender());//点击的按钮
    if (button==nullptr) return;//没找到按钮
    int index=-1;

    for (int i=0;i<9;++i)//遍历所有按钮寻找点击的按钮
    {
        if(buttons[i]==button)
        {
            index=i;
            break;
        }
    }

    if(index==-1) return;
    if(firstSelected==-1)
    {
        firstSelected=index;
        return;
    }
    if(firstSelected==index)//连续点击同一块
    {
        firstSelected=-1;
        return;
    }
    swap(puzzleState[firstSelected], puzzleState[index]);
    firstSelected = -1;
    refreshPuzzle();
    if(isPuzzleSolved())
    {
        QMessageBox::information(this, "YES!", "WIN!!！");//胜利弹窗
    }
}

bool MainWindow::isPuzzleSolved()//检验拼图是否完成
{
    for (int i=0;i<9;++i)
    {
        if(puzzleState[i]!=i) return false;
    }
    return true;
}