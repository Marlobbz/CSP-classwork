#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<bits/stdc++.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)//主构造函数
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //连接数字按钮
    connect(ui->btn0, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &MainWindow::numberClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &MainWindow::numberClicked);
    //连接运算符按钮
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnSub, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMul, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnDiv, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->btnMod, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    //连接点按钮
    connect(ui->btnDot, &QPushButton::clicked, this, &MainWindow::on_btnDot_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//输入输出部分
void MainWindow::numberClicked()//输出数字函数
{
    QPushButton *button = qobject_cast<QPushButton *>(sender()); //找到刚刚被点击的按钮，并把它保存到button

    ui->lineEdit->setText(
        ui->lineEdit->text() + button->text()//获取按钮上的数字
        );
}

void MainWindow::operatorClicked()//输出运算符函数
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    ui->lineEdit->setText(
        ui->lineEdit->text() + button->text()
        );
}

void MainWindow::on_btnDot_clicked()//输出点函数
{
    QString text = ui->lineEdit->text();// 如果当前字符串里面已经包含小数点，直接return，不追加
    if(text.contains("."))
        return;
    ui->lineEdit->setText(text + ".");
}

void MainWindow::on_btnBackspace_clicked()
{
    QString text = ui->lineEdit->text();

    if (!text.isEmpty())
    {
        text.chop(1);//删除字符串最后一个字符
        ui->lineEdit->setText(text);
    }
}

//计算部分

int priority(char op)//定义优先级
{
    if(op=='+'||op=='-')
        return 1;
    if(op=='*'||op=='/'||op=='%')
        return 2;
    return 0;
}

double calculator(stack<double> &numStack,stack<char> &opStack)//定义运算符
{

    double a=numStack.top();
    numStack.pop();
    double b=numStack.top();
    numStack.pop();
    char op=opStack.top();
    opStack.pop();
    if(op=='+')
    {
        return b+a;
    }
    if(op=='-')
    {
        return b-a;
    }
    if(op=='*')
    {
        return b*a;
    }
    if(op=='/')
    {
        if(fabs(a)<1e-9)//除数不为0
        {
            return NAN;
        }
        return b/a;
    }
    if(op=='%')
    {
        if(fabs(a)<1e-12)//取余数不为0
        {
            return NAN;
        }
        return fmod(b,a);//浮点数求余
    }
    return 0;
}

bool isValid(QString expression)//合法性判断
{
    if(expression.isEmpty())//输入为空
        return false;
    if(expression[0]=='+'||expression[0]=='*'||
        expression[0]=='/'||expression[0]=='%')//输入以+*/%开头
        return false;
    int last=expression.length()-1;
    if(expression[last]=='+'||expression[last]=='-'||
        expression[last]=='*'||expression[last]=='/'||expression[last]=='%')//以+*/%结尾
        return false;
    for(int i=0;i<expression.length();i++)
    {
        char current=expression[i].toLatin1();
        if(current=='+'||current=='*'||current=='/'||current=='%')
        {
            if(i+1<expression.length())
            {
                char next=expression[i+1].toLatin1();
                if(next=='+'||next=='*'||next=='/')
                    return false;
            }
        }
        if(current=='-')
        {
            if(i+1<expression.length())
            {
                char next=expression[i+1].toLatin1();
                if(next=='+'||next=='*'||next=='/')
                    return false;
            }
        }

    }
    return true;
}

double calculate(QString expression)
{
    stack<double> numStack;//数字栈
    stack<char> opStack;//运算符栈
    int i=0;
    while(i<expression.length()){
        if(expression[i].isDigit()||expression[i]=='.'||
             (expression[i]=='-'&&(i==0||
                expression[i-1]=='+'||
                expression[i-1]=='-'||
                expression[i-1]=='*'||
                expression[i-1]=='/'||
                expression[i-1]=='%')))
        {
            QString number;
            //如果是计算数就加入number，再转换为double类型存入栈中
            if(expression[i]=='-')
            {
                number+=expression[i];
                i++;
            }
            while(i<expression.length()&&(expression[i].isDigit()||expression[i]=='.'))
            {
                number+=expression[i];
                i++;
            }
            numStack.push(number.toDouble());
        }
        else
        {
            //不是计算数则根据优先级进行出入栈
            char currentOp=expression[i].toLatin1();
            while(!opStack.empty()&&(priority(opStack.top())>=priority(currentOp)))
            {
                double result=calculator(numStack,opStack);
                numStack.push(result);
            }
            opStack.push(currentOp);
            i++;
        }
    }
    while(!opStack.empty())
    {
        double result=calculator(numStack,opStack);
        numStack.push(result);
    }
    return numStack.top();
}

void MainWindow::on_btnEqual_clicked()//=
{
    QString expression = ui->lineEdit->text();
    if(!isValid(expression))
    {
        ui->lineEdit->setText("Error");
        return;
    }
    double result = calculate(expression);
    if(isnan(result))
    {
        ui->lineEdit->setText("Error");
    }
    else
    {
        ui->lineEdit->setText(QString::number(result));
    }
}

void MainWindow::on_btnClear_clicked()//清空键
{
    ui->lineEdit->clear();
}