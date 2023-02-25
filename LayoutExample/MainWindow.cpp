#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QHBoxLayout>
#include <QPushButton>

// 创建一个自动构造并添加到布局的静态函数
static void createButtonIntoLayout(QLayout *layout, int number)
{
    for (int i = 0; i < number; ++i) {
        // 创建一个按钮对象，这里暂不添加到对象树
        QPushButton *button = new QPushButton;
        // 设置按钮的文本
        button->setText(QLatin1String("Button") + QString::number(i));

        // 将该按钮添加到主布局中，添加布局的同时，该按钮就已经被添加到对象树中。
        layout->addWidget(button);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建 MainWindow 的中心控件，并设置到 MainWindow 中
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建主布局，并将布局设置到中心控件 centralWidget 上
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // 调用演示弹簧的函数
    displayStretch(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayMarginAndSpacing(QHBoxLayout *mainLayout)
{
    // 将 mainLayout 的边距设置为 0
    mainLayout->setMargin(0);
    // 将 mainLayout 的间距设置为 0
    mainLayout->setSpacing(0);

    // 创建 4 个按钮
    createButtonIntoLayout(mainLayout, 4);
}

void MainWindow::displayStretch(QHBoxLayout *mainLayout)
{
    // 创建 4 个按钮并添加到主布局中
    createButtonIntoLayout(mainLayout, 4);
    // 创建弹簧
    mainLayout->addStretch();
}

