#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void numberClicked();//输出数字函数
    void operatorClicked();//运算符函输出
    void on_btnDot_clicked();//点
    void on_btnEqual_clicked();//=
    void on_btnClear_clicked();//清空
    void on_btnBackspace_clicked();//退格

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
