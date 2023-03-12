#include "MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QButtonGroup>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);

    examOverloadConnection();
    connectionBindNest();
}

MainWindow::~MainWindow()
{
}

void MainWindow::examConnection()
{
    // 创建中心布局将该布局设置到 centralWidget 界面中
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // 创建按钮并添加到对象树中
    QPushButton *btn1 = new QPushButton(this);
    // 设置按钮的文本为 Button
    btn1->setText("Button");
    // 将按钮的大小策略设置为固定
    btn1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // 函数指针的方式进行信号的绑定。
    connect(btn1, &QPushButton::clicked, this, &MainWindow::onPushButtonClicked);
    // 通过名称的方式进行信号和槽的绑定。
    connect(btn1, SIGNAL(clicked()), this, SLOT(onPushButtonClicked()));

    // 将按钮添加到主布局中
    centralLayout->addWidget(btn1);

    // 设置中心控件为：centralWidget
    setCentralWidget(centralWidget);
}

static void makeButton(QButtonGroup *buttonGroup, QHBoxLayout *layout, int count)
{
    for (int i = 0; i < count; ++i) {
        // 创建按钮
        QPushButton *btn1 = new QPushButton;
        // 设置按钮的文本为 Button + index
        btn1->setText("Button" + QString::number(i));
        // 将按钮的大小策略设置为固定
        btn1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        // 添加到按钮组中
        buttonGroup->addButton(btn1);
        // 添加按钮到布局中
        layout->addWidget(btn1);
    }
}

void MainWindow::examOverloadConnection()
{
    // 创建中心控件并添加到对象树中
    QWidget *centralWidget = new QWidget(this);
    // 设置中心控件为：centralWidget
    setCentralWidget(centralWidget);

    // 创建中心布局将该布局设置到 centralWidget 界面中
    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);

    // 创建按钮组，用于添加多个按钮
    QButtonGroup *buttonGroup = new QButtonGroup(this);

    // 创建四个按钮，并添加到布局中
    makeButton(buttonGroup, centralLayout, 4);

    // 进行 QButtonGroup 的信号槽连接
    // 1. 使用 typedef 进行类型转换
    // // typedef 将带指针的信号函数指针定义为 ButtonClickSignalWithPointer
    // typedef void (QButtonGroup::*ButtonClickSignalWithPointer)(QAbstractButton *);
    // // 通过 static_cast 将 buttongroup 的信号函数指针转换成 ButtonClickSignalWithPointer
    // ButtonClickSignalWithPointer buttonPointer = static_cast<ButtonClickSignalWithPointer>(&QButtonGroup::buttonClicked);
    // // 通过转换后的函数指针进行信号槽的绑定
    // connect(buttonGroup, buttonPointer, this, &MainWindow::onButtonGroupButtonClicked);

    // // 2. 使用 QOverload
    // connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &MainWindow::onButtonGroupButtonClicked);

     // 进行自定义信号槽的绑定
     connect(this, &MainWindow::customButtonClicked, this, &MainWindow::onCustomButtonClicked);

    //信号和信号的连接
     connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &MainWindow::customButtonClicked);
}

void MainWindow::connectionBindLoop()
{
    connect(this, &MainWindow::customButtonClicked, this, &MainWindow::onConnectionBindLoop);
}

void MainWindow::connectionBindNest()
{
    connect(this, &MainWindow::customButtonClicked, this, &MainWindow::onConnectionBindNest);
}

void MainWindow::onPushButtonClicked()
{
    qDebug() << "QPushButton clicked.......";
}

void MainWindow::onButtonGroupButtonClicked(QAbstractButton *button)
{
    qDebug() << button->text() << " clicked....";

    emit customButtonClicked();
}

void MainWindow::onCustomButtonClicked()
{
    qDebug() << "Custom Button clicked......";
}

void MainWindow::onConnectionBindLoop()
{
    qDebug() << "Connection Bind Loop.........";

    emit customButtonClicked();
}

void MainWindow::onConnectionBindNest()
{
    qDebug() << "Connection Nest Bind.........";

    connect(this, &MainWindow::customButtonClicked, this, &MainWindow::onConnectionBindNest);
}
