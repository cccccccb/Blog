#include "Widget.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QTextEdit>
#include <QSplitter>
#include <QScrollArea>
#include <QStackedWidget>
#include <QTabWidget>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(800, 600);

    displayTabWidgetContainer();
}

Widget::~Widget()
{
}

void makeButton(int count, QLayout *layout, QButtonGroup *buttonGroup)
{
    // 编写一个函数用于统一的创建按钮
    for (int i = 0; i < count; ++i) {
        // 创建按钮并设置其文本。
        QPushButton *button = new QPushButton;
        button->setText("Button " + QString::number(i));

        // 设置按钮能够被用户手动选中
        button->setCheckable(true);

        // 将该按钮添加到布局中
        layout->addWidget(button);
        buttonGroup->addButton(button, i);
    }
}

void Widget::displayGroupBoxContainer()
{
    // 创建主布局并设置到当前界面中
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 创建一个 QGroupBox 容器，并创建布局设置到该容器中
    QGroupBox *gb1 = new QGroupBox(this);
    QVBoxLayout *gb1Layout = new QVBoxLayout(gb1);
    // 将该容器添加到主布局中
    mainLayout->addWidget(gb1);
    // 设置容器的标题和对齐方式
    gb1->setTitle("Button Group Box");
    gb1->setAlignment(Qt::AlignLeft);
    // 设置容器的无边框和选中状态
    gb1->setFlat(true);
    gb1->setCheckable(true);
    gb1->setChecked(true);

    // 创建 QButtonGroup 并添加到对象树中。
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    connect(buttonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this, &Widget::onDisplayButtonGroupClicked);

    // 创建 5 个按钮
    makeButton(5, gb1Layout, buttonGroup);
    gb1Layout->addStretch();
}

void Widget::displaySplitterContainer()
{
    // 创建主布局并设置到当前界面中
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 创建 Label1, 设置文本并添加到对象树中。
    QLabel *label1 = new QLabel("Label 1", this);

    // 创建一个多行文本输入框，并添加到对象树中。
    QTextEdit *textEdit = new QTextEdit(this);

    // 创建一个用于显示图片的 Label 并添加到对象树中。
    QLabel *label2 = new QLabel(this);
    // 读取从资源文件中访问到的图片数据
    label2->setPixmap(QPixmap(":/img/SplitterLabelImage.png"));

    // 创建 splitter 控件并添加到主布局中
    QSplitter *splitter = new QSplitter(this);
    mainLayout->addWidget(splitter);

    // 添加 splitter 内排列的子控件
    splitter->addWidget(label1);
    splitter->addWidget(textEdit);
    splitter->addWidget(label2);

    // 设置 splitter 控件的方向为水平方向
    splitter->setOrientation(Qt::Vertical);

    // 设置 splitter 控件的每个控件的固定大小
    splitter->setSizes({10, 200, 200});
    // 设置子控件不会被拖拽隐藏
    splitter->setChildrenCollapsible(false);

    // 设置 splitter 控件内子控件被添加后的布局系数
    // splitter->setStretchFactor(0, 1);
    // splitter->setStretchFactor(1, 2);
    // splitter->setStretchFactor(2, 1);
}

void Widget::displayFrameContainer()
{
    // 创建主布局并设置到当前界面中
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 创建一个主背景的 Frame 容器
    QFrame *frameMain = new QFrame(this);
    // 添加到主布局中
    mainLayout->addWidget(frameMain);
    // 修改 frameMain 的线样式，并调整线宽
    frameMain->setFrameShape(QFrame::StyledPanel);
    frameMain->setLineWidth(2);

    // 创建 frameMain 的布局并设置到 frameMain 中
    QHBoxLayout *frameMainLayout = new QHBoxLayout(frameMain);

    // 创建一个 子 Box 类型的 Frame 容器
    QFrame *frameBox = new QFrame(this);
    frameBox->setFrameShape(QFrame::Box);
    frameBox->setFrameShadow(QFrame::Raised);
    frameBox->setLineWidth(5);
    frameBox->setMidLineWidth(2);
    // 添加到 frameMain 布局中
    frameMainLayout->addWidget(frameBox);

    // 创建一个水平分割线的 Frame
    QFrame *frameHLine = new QFrame(this);
    frameHLine->setFrameShape(QFrame::HLine);
    // 添加到 frameMain 布局中
    frameMainLayout->addWidget(frameHLine);

    // 创建一个竖直分割线的 Frame
    QFrame *frameVLine = new QFrame(this);
    frameVLine->setFrameShape(QFrame::VLine);
    // 添加到 frameMain 布局中
    frameMainLayout->addWidget(frameVLine);
}

void Widget::displayScrollAreaContainer()
{
    // 创建主布局并设置到当前界面中
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 创建滚动区域控件并添加到对象树中
    QScrollArea *scrollArea = new QScrollArea(this);
    // 将滚动区域添加到主布局中
    mainLayout->addWidget(scrollArea);

    // 创建一个存储我们界面显示不下的大量控件的容器
    QWidget *scrollContainer = new QWidget(this);
    // 创建一个布局用于存放这些子控件
    QVBoxLayout *scrollContainerLayout = new QVBoxLayout(scrollContainer);

    // 我们需要使用到 makeButton 函数用于创建很多按钮
    makeButton(100, scrollContainerLayout, new QButtonGroup(this));

    // 下面需要将 scrollContainer 和 scrollArea 进行联动
    // setWidget 函数可以添加用于显示容器的主体
    scrollArea->setWidget(scrollContainer);
    // 我们需要让 scrollContainer 和 scrollArea保持同样的大小调整方式
    // 因此需要将下面的属性打开
    scrollArea->setWidgetResizable(true);
}

void Widget::displayStackedWidgetContainer()
{
    // 创建主布局并设置到当前界面中
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建一个容器1，并创建其布局
    QWidget *container1 = new QWidget(this);
    QHBoxLayout *container1Layout = new QHBoxLayout(container1);

    // 创建一个文本 label并设置其文本
    QLabel *label1 = new QLabel("Label1", this);
    // 设置文本的居中显示
    label1->setAlignment(Qt::AlignCenter);
    // 添加文本到第一个容器中
    container1Layout->addWidget(label1);

    // 创建一个容器2，并创建其布局
    QWidget *container2 = new QWidget(this);
    QHBoxLayout *container2Layout = new QHBoxLayout(container2);

    // 创建一个按钮并设置其文本
    QPushButton *button1 = new QPushButton("Button1", this);
    // 添加到容器2 中
    container2Layout->addWidget(button1);

    // 创建一个容器2，并创建其布局
    QWidget *container3 = new QWidget(this);
    QHBoxLayout *container3Layout = new QHBoxLayout(container3);

    // 创建一个多行文本输入控件，并添加到容器内
    QTextEdit *textEdit = new QTextEdit(this);
    container3Layout->addWidget(textEdit);

    // 创建一个 QStackedWidget 控件并添加到对象树中
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    // 将 stackedWidget 添加到主布局中
    mainLayout->addWidget(stackedWidget);

    // 将这些容器全部添加到 stackedWidget 中
    stackedWidget->addWidget(container1);
    stackedWidget->addWidget(container2);
    stackedWidget->addWidget(container3);

    // 下面我们需要添加一下 如果切换这些页面的入口
    QHBoxLayout *buttonLayout = new QHBoxLayout(this);
    // 将按钮布局添加到主布局中
    mainLayout->addLayout(buttonLayout);

    // 创建一个按钮组用户添加切换的按钮
    QButtonGroup *butonGroup = new QButtonGroup(this);
    makeButton(3, buttonLayout, butonGroup);
    // 我们添加一个弹簧来保证按钮的弹性收缩
    buttonLayout->addStretch();

    // 我们需要绑定一下 butonGroup 的按钮选中信号，用于手动选中后的自由切换
    // 我们使用匿名函数，在槽函数中，我们通常能够使用匿名函数进行简单的函数实现
    // 匿名函数是 c++11 的内容，对匿名函数不熟悉的同学可以复习一下匿名函数的使用
    connect(butonGroup, QOverload<int, bool>::of(&QButtonGroup::buttonToggled), this,
            [stackedWidget](int index, bool checked) {
        if (!checked)
            return;

        stackedWidget->setCurrentIndex(index);
    });

    // 最后 我们需要将默认的 stackedWidget 设置为某一页
    stackedWidget->setCurrentIndex(0);
    // 例如我们上述将索引为 0 的页面设置为第一页，那我们就将
    // 第一个按钮的设置为 checked 状态，这属于是初始显示的一致。
    butonGroup->button(0)->setChecked(true);
}

void Widget::displayTabWidgetContainer()
{
    // 创建主布局并设置到当前界面中
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建 QTabWidget 控件并添加到对象树中
    QTabWidget *tabWidget = new QTabWidget(this);
    // 设置 tab 的从左到右显示, 也就是西边
    tabWidget->setTabPosition(QTabWidget::West);
    // 将 QTabWidget 对象添加到主布局中
    mainLayout->addWidget(tabWidget);

    // 创建容器1 和其布局器，并添加到对象树中
    QWidget *container1 = new QWidget(this);
    QHBoxLayout *container1Layout = new QHBoxLayout(container1);

    // 创建一个用于显示图片的 Label 并添加到对象树中。
    QLabel *labelImage = new QLabel(this);
    // 读取从资源文件中访问到的图片数据
    labelImage->setPixmap(QPixmap(":/img/SplitterLabelImage.png"));
    // 将图片添加到容器1的布局中，并居中排列
    container1Layout->addWidget(labelImage, 0, Qt::AlignCenter);

    // 创建容器2 和其布局器，并添加到对象树中
    QWidget *container2 = new QWidget(this);
    QHBoxLayout *container2Layout = new QHBoxLayout(container2);

    // 创建一个多行文本输入控件，并添加到容器内
    QTextEdit *textEdit = new QTextEdit(this);
    container2Layout->addWidget(textEdit);

    // 将这些容器添加到 QTabWidget 中
    tabWidget->addTab(container1, "Image Tab");
    tabWidget->addTab(container2, "TextEdit Tab");
}

void Widget::onDisplayButtonGroupClicked(QAbstractButton *button)
{
    qDebug() << button->text() << " Button Clicked........";
}

