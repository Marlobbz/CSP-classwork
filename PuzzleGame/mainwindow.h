#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    bool loadPuzzleImage();

    QVector<QPushButton*> buttons;//动态保存拼图按钮
    QVector<QPixmap> puzzleImages;//动态保存每块拼图的图片
    QVector<int> puzzleState;//动态保存每个位置对应的图片编号
    int puzzleRows = 3; // 当前拼图行数
    int puzzleCols = 3; // 当前拼图列数
    void createPuzzleButtons();//根据当前行数和列数创建拼图按钮
    void choosePuzzleSize();//自定义拼图行数和列数

    void shufflePuzzle();
    void refreshPuzzle();
    void puzzleButtonClicked();
    int firstSelected = -1;//第一次点击的位置
    //基础功能
    bool isPuzzleSolved();//检测拼图是否完成

    QPixmap originalImage;//保存完整的原图
    QString currentImagePath;//记录当前图片编号
    void showOriginalImage();//显示原图
    void changeRandomImage();//随机换图
    void restartGame(); //重新开始当前游戏

    void chooseImage();//添加图片
    //计时
    void updateGameTime();//更新时间显示
    void startGameTimer();//开始计时
    void resetGameStats();//重置统计数据
    void stopGameTimer();//停止计时
    void updateStepsLabel(); //更新步数显示

    QTimer *gameTimer;//游戏计时器，每秒触发一次
    int elapsedSeconds=0;//已用时间，单位秒
    int steps=0;//成功交换的次数
    bool gameStarted=false;//是否已经开始计时
    bool gameFinished=false;//标记游戏是否已经完成

    //最佳成绩记录
    void loadBestScores();//读取历史最佳成绩
    void updateBestScores();//更新最佳成绩
    void refreshBestScores();//刷新成绩显示
    int bestTime=-1;//最佳用时-1表示暂无记录
    int bestSteps=-1;//最少步数-1表示暂无记录
};
#endif // MAINWINDOW_H
