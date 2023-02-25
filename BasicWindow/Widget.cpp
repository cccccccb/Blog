#include "Widget.h"

#include <QHBoxLayout>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{
    initUI();
}

void Widget::initUI()
{
    // 构建主布局，并添加到对象树中，同时当前 Widget 的布局自动被设置为 mainLayout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 创建按钮并增加到对象树中。
    QPushButton *button1 = new QPushButton(this);
    button1->setText("Button1");
    QPushButton *button2 = new QPushButton(this);
    button2->setText("Button2");

    // 将按钮添加到布局中
    mainLayout->addWidget(button1);
    mainLayout->addWidget(button2);
}
