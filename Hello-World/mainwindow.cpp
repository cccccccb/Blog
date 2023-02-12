#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QToolButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

#if 0
    QWidget *centralWidget = new QWidget(this);
    // 创建对象，并添加到对象树，并将 centralWidget 的布局设置为 vlayout
    QHBoxLayout *vlayout =  new QHBoxLayout(centralWidget);

    QPushButton *button1 = new QPushButton(this);
    button1->setText("button1");

    QPushButton *button2 = new QPushButton(this);
    button2->setText("button2");

    vlayout->addWidget(button1);
    vlayout->addWidget(button2);
    setCentralWidget(centralWidget);
#else
#if 1
    // 开始添加测试代码
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建水平布局，并设置到 centralWidget 中
    QHBoxLayout *hlayout = new QHBoxLayout(centralWidget);

    QLabel *label = new QLabel(this);
    label->setText("右侧是图片和按钮");
    // 将文字的排列方式设置为靠右和垂直居中
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    hlayout->addWidget(label);

    // 创建垂直布局，暂不设置到任何控件中
    QVBoxLayout *vlayout = new QVBoxLayout;

    // 创建并添加到对象数
    QLabel *imageLabel = new QLabel(this);
    imageLabel->setFixedSize(150, 90);
    // 设置 Label 的图片资源
    imageLabel->setPixmap(QPixmap(":/icons/img/OIP.jpg"));
    // 设置图片资源自动缩放到当前大小，防止内容发生截断
    imageLabel->setScaledContents(true);
    // 控制内部控件的排列方式为水平居中加底部对齐
    vlayout->addWidget(imageLabel, 0, Qt::AlignHCenter | Qt::AlignBottom);

    // 创建一个 button 对象，并添加到 Qt 的对象树中。
    QPushButton *button = new QPushButton(this);
    // 设置按钮显示的文本
    button->setText("button");

    // 控制内部控件的排列方式为水平居中加顶部对齐
    vlayout->addWidget(button, 0, Qt::AlignHCenter | Qt::AlignTop);

    // 将vlayout添加到hlayout内部进行控制，这也会添加到对象数中。
    hlayout->addLayout(vlayout);
#else
    // 开始添加测试代码
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建对象，并添加到对象树，并将 centralWidget 的布局设置为 vlayout
    QVBoxLayout *vlayout =  new QVBoxLayout(centralWidget);

    // 创建一个 button 对象，并添加到 Qt 的对象树中。
    QPushButton *button = new QPushButton(this);
    // 设置按钮显示的文本
    button->setText("button");

    // 开始设置按钮图标
    button->setIcon(QIcon(":/icons/img/apple_line.png"));

    // 添加控件到布局中
    vlayout->addWidget(button);

    // 同样的将 toolButton 增加到对象树中。
    QToolButton *toolButton = new QToolButton(this);

    // 设置图标和文本
    toolButton->setIcon(QIcon(":/icons/img/apple_line.png"));
    toolButton->setText("Tool Button");

    // 设置图标和文本的排列类型
    toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // 添加控件到布局中
    vlayout->addWidget(toolButton);

    // 创建并增加到对象数
    QRadioButton *radioButton1 = new QRadioButton(this);

    radioButton1->setText("radio button1");
    vlayout->addWidget(radioButton1);

    // 创建并增加到对象数
    QRadioButton *radioButton2 = new QRadioButton(this);

    radioButton2->setText("radio button2");
    // 可以进行选中和未选中的设置
    radioButton2->setChecked(true);
    vlayout->addWidget(radioButton2);

    // 创建并增加到对象数，这里增加到对象树的目的是无需手动管理内存
    QButtonGroup *buttonGroup = new QButtonGroup(this);

    // 添加到 QButtonGroup 中用于控制按钮的选中和非选中
    buttonGroup->addButton(radioButton1);
    buttonGroup->addButton(radioButton2);

    // 创建并添加到对象树
    QCheckBox *checkBox = new QCheckBox(this);
    checkBox->setText("check box");
    vlayout->addWidget(checkBox);

    // 创建并添加到对象数
    QLabel *label = new QLabel(this);
    label->setText("Label");

    vlayout->addWidget(label);

    // 创建并添加到对象数
    QLabel *imageLabel = new QLabel(this);
    // 设置 Label 的图片资源
    imageLabel->setPixmap(QPixmap(":/icons/img/OIP.jpg"));
    // 设置图片资源自动缩放到当前大小，防止内容发生截断
    imageLabel->setScaledContents(true);

    vlayout->addWidget(imageLabel);
#endif
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

