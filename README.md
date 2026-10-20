# CSP-classwork

中国矿业大学（CUMT）CSP课程大作业。

本仓库用于存放课程实验、课程设计及相关实验报告。

## 实验项目

### 1. Calculator —— 基于 Qt 的简易计算器

使用 **C++ / Qt** 实现的简易计算器，支持连续四则运算，并使用双栈算法完成表达式解析与计算。

**项目内容：**

* Qt 图形化界面
* 四则运算
* 连续表达式计算
* 小数计算
* 括号及运算符优先级处理
* 双栈表达式求值
* 基本输入合法性判断

**相关文件：**

* [Calculator 项目源码](./Calculator/)
* [Calculator 实验报告](./Calculator/REPORT.md)

---

### 2. PuzzleGame —— 基于 Qt 的拼图游戏

使用 **C++ / Qt 6** 实现的图形化拼图游戏。玩家可以通过点击两块拼图交换位置，将打乱的图片恢复为正确排列，并支持自定义拼图难度。

**项目内容：**

* Qt 图形化游戏界面
* 拼图图片加载、裁剪与分割
* 点击交换拼图块及完成状态判断
* 随机切换内置图片、选择本地图片
* 查看原图与重新开始游戏
* 自定义拼图行数和列数（2～10）
* 游戏计时、步数统计及最佳成绩记录
ps:学会用visio画图啦！
**相关文件：**

* [PuzzleGame 项目源码](./PuzzleGame/)
* [PuzzleGame 实验报告](./PuzzleGame/REPORT.md)

---

## 仓库结构

```text
CSP-classwork/
├── Calculator/
│   ├── REPORT.md
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── mainwindow.ui
│   └── ...
│
├── PuzzleGame/
│   ├── REPORT.md
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   ├── mainwindow.ui
│   ├── resources.qrc
│   └── ...
│
└── README.md
```

## 开发环境

* C++
* Qt
* Qt Creator
* CMake
* STL

## 说明

本仓库仅用于记录 CSP 课程相关的实验代码、实验报告以及课程设计资料。

---

**Author:** [Marlobbz](https://github.com/Marlobbz)
