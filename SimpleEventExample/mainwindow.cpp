#include "mainwindow.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPushButton>

#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    setMouseTracking(true);
    examEventCall();
}

MainWindow::~MainWindow()
{
}

void MainWindow::examCreateEventByManual()
{
    // 创建中心控件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建中心布局
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // 创建按钮
    QPushButton *button = new QPushButton(this);
    // 设置按钮文本
    button->setText("点击按钮创建鼠标移动事件!");
    // 将按钮设置为固定大小
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // 绑定按钮点击的槽函数
    connect(button, &QPushButton::clicked, this, &MainWindow::onExamCreateEventByManual);

    // 中心布局中添加该按钮,并进行居中放置
    centralLayout->addWidget(button, 0, Qt::AlignCenter);
}

void MainWindow::examEventFilterOnChildWidget()
{
    // 创建中心控件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建中心布局
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // 创建按钮
    QPushButton *button = new QPushButton(this);
    // 成员变量先暂时保存该地址，用于事件过滤器的比较
    m_filterWidget = button;
    // 设置按钮文本
    button->setText("事件过滤器的测试按钮");
    // 将按钮设置为固定大小
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // 安装事件过滤器，需要被当前控件进行过滤
    button->installEventFilter(this);
    // 绑定按钮点击的槽函数
    connect(button, &QPushButton::clicked, this, &MainWindow::onExamCreateEventByManual);

    // 中心布局中添加该按钮,并进行居中放置
    centralLayout->addWidget(button, 0, Qt::AlignCenter);
}

void MainWindow::examEventCall()
{
    // 创建中心控件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建中心布局
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // 创建按钮
    QPushButton *button = new QPushButton(this);
    // 设置按钮文本
    button->setText("事件的测试按钮");
    // 将按钮设置为固定大小
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // 绑定按钮点击的槽函数
    connect(button, &QPushButton::clicked, this, &MainWindow::onExamCreateEventByManual);

    // 中心布局中添加该按钮,并进行居中放置
    centralLayout->addWidget(button, 0, Qt::AlignCenter);
}

void MainWindow::onExamCreateEventByManual()
{
//    QMouseEvent mouseMove(QEvent::MouseMove, {0, 0}, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

//    qApp->sendEvent(this, &mouseMove);

    QMouseEvent *mouseMove = new QMouseEvent(QEvent::MouseMove, {0, 0}, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

    qApp->postEvent(this, mouseMove);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse pressed............";
    return QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse Moving............";
    return QMainWindow::mouseMoveEvent(event);
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::MouseMove) {
        qDebug() << "Event: Mouse Moving............";
    }

    return QWidget::event(event);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_filterWidget) {
        if (event->type() == QEvent::MouseButtonPress) {
            qDebug() << "过滤鼠标按下事件";
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}

