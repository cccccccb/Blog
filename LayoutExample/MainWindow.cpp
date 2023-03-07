#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QHBoxLayout>
#include <QLabel>
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

    displaySizePolicyStretch(mainLayout);
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


void MainWindow::displayStretchFactor(QHBoxLayout *mainLayout)
{
    // 创建一个按钮并添加到对象树中
    QPushButton *button = new QPushButton(this);
    button->setText("Button");
    // 添加按钮到主布局中, 并设置其弹性因子为 1
    mainLayout->addWidget(button, 1);

    // 创建一个文本标签并添加到对象树中
    QLabel *label = new QLabel(this);
    label->setText("This is a very very very very very very long sentence.");
    // 为了方便演示，我们将文本的文字排列使用为右对齐，以演示文本标签的具体大小
    // 使用右对齐和垂直居中对齐的混合方式
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    // 添加文本标签到对象树中, 并调整其弹簧系数为 2
    mainLayout->addWidget(label, 2);
}

void MainWindow::displaySizePolicy(QHBoxLayout *mainLayout)
{
    // 创建一个按钮并添加到对象树中
    QPushButton *button = new QPushButton(this);
    button->setText("Button");
    // 添加按钮到主布局中
    mainLayout->addWidget(button);

    // 创建一个文本标签并添加到对象树中
    QLabel *label = new QLabel(this);
    label->setText("This is a very very very very very very long sentence.");

    // 调整按钮的大小策略，水平方向调整为扩大，垂直方向跟随默认策略。
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    // 添加文本标签到主布局中
    mainLayout->addWidget(label);
}

static void adjustStretchFactorBySizePolicy(QWidget *widget, int stretchFactor)
{
    QSizePolicy sizePolicy = widget->sizePolicy();

    sizePolicy.setHorizontalStretch(stretchFactor);
    widget->setSizePolicy(sizePolicy);
}

void MainWindow::displaySizePolicyStretch(QHBoxLayout *mainLayout)
{
    // 创建一个按钮并添加到对象树中
    QPushButton *button = new QPushButton(this);
    button->setText("Button");
    adjustStretchFactorBySizePolicy(button, 1);
    // 添加按钮到主布局中
    mainLayout->addWidget(button, 5);

    // 创建一个文本标签并添加到对象树中
    QLabel *label = new QLabel(this);
    label->setText("This is a very very very very very very long sentence.");
    adjustStretchFactorBySizePolicy(label, 2);

    // 添加文本标签到主布局中
    mainLayout->addWidget(label, 2);
}
