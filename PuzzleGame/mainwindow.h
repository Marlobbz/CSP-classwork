#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>

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
    void loadPuzzleImage();

    QPushButton* buttons[9];
    QPixmap puzzleImages[9];//保存9张拼图图片
    int puzzleState[9];//保存当前位置对应的图片编号
    int selected = -1;//记录点击的拼图块

    void swapPuzzle(int a, int b);
    bool canSwap(int a, int b);

    void shufflePuzzle();
    void refreshPuzzle();
    void puzzleButtonClicked();
    int firstSelected = -1;//第一次点击的位置

    bool isPuzzleSolved();//检测拼图是否完成
};
#endif // MAINWINDOW_H
