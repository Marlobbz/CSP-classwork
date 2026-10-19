#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QSettings>
#include <QSizePolicy>
#include <QGridLayout>
#include <QVector>
#include <QPixmap>
#include <QInputDialog>
#include <bits/stdc++.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //连接功能按钮
    connect(ui->showOriginalButton, &QPushButton::clicked,this, &MainWindow::showOriginalImage);
    connect(ui->randomImageButton, &QPushButton::clicked,this, &MainWindow::changeRandomImage);
    connect(ui->chooseImageButton, &QPushButton::clicked,this, &MainWindow::chooseImage);
    connect(ui->restartButton, &QPushButton::clicked,this, &MainWindow::restartGame);
    connect(ui->difficultyButton, &QPushButton::clicked,this, &MainWindow::choosePuzzleSize);
    //设置拼图区域
    ui->layoutWidget->setGeometry(180,20,600,600);
    ui->gridLayout_2->setSpacing(0);
    ui->gridLayout_2->setContentsMargins(0,0,0,0);
    //动态创建拼图按钮
    createPuzzleButtons();
    //初始化图片和拼图
    currentImagePath=":/image/test.png";
    if (loadPuzzleImage())
    {
        shufflePuzzle();
        refreshPuzzle();
        //等布局完成后，再刷新一次
        QTimer::singleShot(0,this,[this](){refreshPuzzle();});
    }
    //再刷新一次，确定按钮尺寸
    QTimer::singleShot(0,this,[this](){refreshPuzzle();});

    //初始化计时器
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout,this, &MainWindow::updateGameTime);
    resetGameStats();
    loadBestScores();//读取历史最佳成绩
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createPuzzleButtons()//创建按钮函数
{
    //先清除网格布局中的旧按钮，避免切换难度后按钮叠加
    while(QLayoutItem*item=ui->gridLayout_2->takeAt(0))
    {
        if(QWidget *widget=item->widget())
        {
            delete widget;
        }

        delete item;
    }
    buttons.clear();//清空按钮指针集合
    //根据当前行数和列数创建按钮
    int total=puzzleRows*puzzleCols;
    for(int i=0;i<total;i++)
    {
        QPushButton *button = new QPushButton(ui->layoutWidget);
        button->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
        button->setStyleSheet(
            "QPushButton{"
            "border:0px;"
            "padding:0px;"
            "margin:0px;"
            "background:transparent;"
            "}"
            );
        buttons.append(button);
        //根据一维编号计算按钮所在的行和列
        int row=i/puzzleCols;//行
        int col=i%puzzleCols;//列
        ui->gridLayout_2->addWidget(button,row,col);
        //为新按钮连接点击事件
        connect(button, &QPushButton::clicked,this,&MainWindow::puzzleButtonClicked);
    }
}

void MainWindow::choosePuzzleSize()//自定义难度
{
    bool ok=false;
    //输入拼图行数，范围为2-10
    int rows = QInputDialog::getInt(
        this,
        "Difficulty",
        "row：",
        puzzleRows,
        2, 10, 1,
        &ok
        );
    //如果取消输入，保留原来的拼图
    if (!ok) return;
    //输入拼图列数,范围为2-10
    int cols = QInputDialog::getInt(
        this,
        "Difficulty",
        "col：",
        puzzleCols,
        2, 10, 1,
        &ok
        );
    //如果取消输入，同样不修改原来的拼图
    if(!ok) return;
    //保存新的行数和列数
    puzzleRows=rows;
    puzzleCols=cols;
    //清除之前选中的拼图块
    firstSelected = -1;
    //按新的尺寸重建按钮
    createPuzzleButtons();
    //重新切图、打乱拼图并重置统计数据
    loadPuzzleImage();
    shufflePuzzle();
    resetGameStats();
    refreshPuzzle();//刷新拼图显示
    //等布局完成后再刷新一次，确保图片尺寸正确
    QTimer::singleShot(0, this, [this]() {refreshPuzzle();});
}

//功能部分：

bool MainWindow::loadPuzzleImage() // 加载、裁剪、切分并初始化拼图数据
{
    //根据当前路径加载图片
    QPixmap image(currentImagePath);
    if(image.isNull())//加载失败时，直接返回 false
    {
        QMessageBox::warning(this,"Error","No picture！");
        return false;
    }
    originalImage=image;//保存原图，用于查看原图功能
    //根据当前行列数计算拼图整体的目标宽高比例
    double targetRatio=static_cast<double>(puzzleCols)/puzzleRows;
    int cropWidth=image.width();
    int cropHeight=image.height();
    //居中裁剪，使图片比例与拼图整体比例一致
    if(static_cast<double>(image.width())/image.height()>targetRatio)
    {
        cropWidth=static_cast<int>(image.height()*targetRatio);
    }
    else
    {
        cropHeight=static_cast<int>(image.width()/targetRatio);
    }
    int x=(image.width()-cropWidth)/2;
    int y=(image.height()-cropHeight)/2;
    image=image.copy(x,y,cropWidth,cropHeight);
    //清除上一次的拼图数据
    puzzleImages.clear();
    puzzleState.clear();
    int total=puzzleRows*puzzleCols;
    //按照当前行数和列数切分图片
    for(int i=0;i<total;i++)
    {
        int row=i/puzzleCols;//行
        int col=i%puzzleCols;//列
        //计算当前拼图块的边界
        int x1=col*image.width()/puzzleCols;
        int x2=(col+1)*image.width()/puzzleCols;
        int y1=row*image.height()/puzzleRows;
        int y2=(row+1)*image.height()/puzzleRows;
        QPixmap piece=image.copy(x1,y1,x2-x1,y2-y1);
        //保存拼图块，并记录其初始编号
        puzzleImages.append(piece);
        puzzleState.append(i);
    }
    return true;//图片加载和切分成功
}
////////////////////////////////////////////////////////查看原图
void MainWindow::showOriginalImage()//查看原图函数
{
    QDialog dialog(this);
    dialog.setWindowTitle("原图");

    QLabel label(&dialog);

    QPixmap showImage = originalImage.scaled(//根据窗口大小自动缩放图片
        600,
        600,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
        );

    label.setPixmap(showImage);
    label.setAlignment(Qt::AlignCenter);

    QVBoxLayout layout(&dialog);
    layout.addWidget(&label);

    dialog.exec();
}

void MainWindow::shufflePuzzle()//打乱拼图块的排列顺序
{
    //计算当前拼图块总数
    int total=puzzleRows*puzzleCols;
    //生成所有拼图块的初始编号
    puzzleState.clear();
    for (int i=0;i<total;i++)
    {
        puzzleState.append(i);
    }
    //随机打乱编号顺序
    random_device rd;
    mt19937 g(rd());
    shuffle(puzzleState.begin(), puzzleState.end(), g);
}

void MainWindow::refreshPuzzle()
{
    //遍历当前所有拼图按钮
    for(int i=0;i<buttons.size();i++)
    {
        QSize target=buttons[i]->size();//获取当前按钮的实际尺寸
        if(target.isEmpty()) continue;//如果按钮还没有有效尺寸，暂时跳过
        int imageIndex = puzzleState[i];//根据拼图状态找到对应图片
        //缩放图片并显示在按钮上
        QPixmap scaledImage = puzzleImages[imageIndex].scaled(
            target,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
            );
        buttons[i]->setIcon(QIcon(scaledImage));
        buttons[i]->setIconSize(target);
    }
}
////////////////////////////////////////////////////////随机换图
void MainWindow::changeRandomImage()
{
    QString imagePaths[3]=
        {
            ":/image/test.png",
            ":/image/test2.png",
            ":/image/test3.png"
        };
    random_device rd;
    mt19937 g(rd());
    uniform_int_distribution<int> dist(0,2);
    QString newPath;
    //避免连续选择当前图片
    do
    {
        newPath=imagePaths[dist(g)];
    }
    while (newPath==currentImagePath);
    //保存原来的图片路径
    QString oldPath=currentImagePath;
    currentImagePath=newPath;
    //加载失败则恢复原路径不继续操作
    if (!loadPuzzleImage())
    {
        currentImagePath=oldPath;
        return;
    }
    //加载成功后开始新一局
    shufflePuzzle();
    firstSelected = -1;
    resetGameStats();
    refreshPuzzle();
}
////////////////////////////////////////////////////////自定义图片
void MainWindow::chooseImage()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "选择图片",
        "",
        "图片文件 (*.png *.jpg *.jpeg *.bmp)"
        );
    //取消选择时不做任何操作
    if(fileName.isEmpty()) return;
    //暂存原来的图片路径
    QString oldPath=currentImagePath;
    //尝试加载新图片
    currentImagePath=fileName;
    if(!loadPuzzleImage())
    {
        //加载失败恢复原路径并保留原游戏状态
        currentImagePath=oldPath;
        return;
    }
    //只有加载成功，才开始新一局
    shufflePuzzle();
    firstSelected = -1;
    resetGameStats();
    refreshPuzzle();
}



////////////////////////////////////////////////////////重新游戏
void MainWindow::restartGame()
{
    firstSelected=-1;//清除上一次的选中状态
    shufflePuzzle();//重新打乱当前拼图
    resetGameStats();//重置计时与步数
    refreshPuzzle();//刷新拼图显示
}

//交换部分：
////////////////////////////////////////////////////////点击函数
void MainWindow::puzzleButtonClicked()
{
    if (gameFinished) return;//如果游戏已经完成，不再允许交换拼图
    QPushButton *button = qobject_cast<QPushButton*>(sender());//获取触发点击事件的按钮
    if (button == nullptr) return;
    // 查找这个按钮在动态按钮容器中的编号
    int index=buttons.indexOf(button);
    if(index==-1) return;
    // 第一次点击：记录选中的位置
    if(firstSelected==-1)
    {
        firstSelected=index;
        return;
    }
    //再次点击同一块：取消选择
    if(firstSelected==index)
    {
        firstSelected=-1;
        return;
    }
    startGameTimer();//开始游戏计时
    swap(puzzleState[firstSelected], puzzleState[index]);//交换两个位置对应的图片编号
    steps++;//交换成功，步数加一
    updateStepsLabel();
    firstSelected=-1;//清除选中状态
    refreshPuzzle();//刷新界面
    if(isPuzzleSolved())//判断是否完成
    {
        gameFinished=true;
        stopGameTimer();
        updateBestScores();
        QMessageBox::information(
            this,
            "Win",
            QString("Finish！\ntime：%1m%2s\nstep：%3step")
                .arg(elapsedSeconds/60)
                .arg(elapsedSeconds%60)
                .arg(steps)
            );
    }
}

bool MainWindow::isPuzzleSolved()//判断是否完成拼图
{
    for (int i=0;i<puzzleState.size();i++)
    {
        if(puzzleState[i]!=i) return false;//每个位置上的图片编号与位置编号一致
    }
    return true;
}
////////////////////////////////////////////////////////游戏计时
// 开始游戏计时
void MainWindow::startGameTimer()
{
    if (gameStarted) return;
    gameStarted = true;
    gameTimer->start(1000);
}
//更新时间显示
void MainWindow::updateGameTime()
{
    elapsedSeconds++;
    int minutes=elapsedSeconds/60;
    int seconds=elapsedSeconds%60;

    ui->timeLabel->setText(
        QString("时间：%1:%2")
            .arg(minutes,2,10,QChar('0'))
            .arg(seconds,2,10,QChar('0'))
        );
}

//更新步数显示
void MainWindow::updateStepsLabel()
{
    ui->stepsLabel->setText( QString("步数：%1").arg(steps));
}

//重置游戏统计
void MainWindow::resetGameStats()
{
    gameTimer->stop();

    elapsedSeconds=0;
    steps=0;
    gameStarted=false;
    gameFinished=false;

    ui->timeLabel->setText("时间：00:00");
    updateStepsLabel();
}

//停止计时
void MainWindow::stopGameTimer()
{
    gameTimer->stop();
    gameStarted=false;
}

//读取本地保存的最佳成绩
void MainWindow::loadBestScores()
{
    QSettings settings("Marlobbz", "PuzzleGame");

    // 如果没有保存过成绩，就使用 -1 表示暂无记录
    bestTime = settings.value("bestTime", -1).toInt();
    bestSteps = settings.value("bestSteps", -1).toInt();

    // 更新界面显示
    refreshBestScores();
}
//刷新最佳成绩的界面显示
void MainWindow::refreshBestScores()
{
    // 显示最佳用时
    if (bestTime == -1)
    {
        ui->bestTimeLabel->setText("最佳用时：暂无");
    }
    else
    {
        int minutes = bestTime / 60;
        int seconds = bestTime % 60;

        ui->bestTimeLabel->setText(
            QString("最佳用时：%1:%2")
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'))
            );
    }

    // 显示最少步数
    if (bestSteps == -1)
    {
        ui->bestStepsLabel->setText("最少步数：暂无");
    }
    else
    {
        ui->bestStepsLabel->setText(
            QString("最少步数：%1 步").arg(bestSteps)
            );
    }
}

//比较本局成绩并保存新的最佳成绩
void MainWindow::updateBestScores()
{
    QSettings settings("Marlobbz", "PuzzleGame");

    bool changed=false;
    // 首次完成游戏，或本局用时更短
    if (bestTime==-1||elapsedSeconds<bestTime)
    {
        bestTime=elapsedSeconds;
        settings.setValue("bestTime", bestTime);
        changed=true;
    }
    // 首次完成游戏，或本局步数更少
    if (bestSteps==-1||steps<bestSteps)
    {
        bestSteps = steps;
        settings.setValue("bestSteps", bestSteps);
        changed = true;
    }
    // 有成绩更新时，将数据写入持久化存储
    if (changed)
    {
        settings.sync();
    }
    refreshBestScores();
}
