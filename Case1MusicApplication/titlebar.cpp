#include "titlebar.h"

#include <QAction>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("TitleBar");
    initUi();
}

void TitleBar::initUi()
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(50);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // 行输入框的控件名称为 QLineEdit
    QLineEdit *searchEdit = new QLineEdit(this);
    // 添加 Placeholder 文本
    searchEdit->setPlaceholderText("Search for something...");
    // 尾部的图标我们需要通过添加 Action 的接口添加进去
    searchEdit->addAction(new QAction(QIcon(":/img/imgs/Search.png"), ""), QLineEdit::TrailingPosition);
    searchEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    searchEdit->setFixedWidth(180);

    QPushButton *minButton = new QPushButton(this);
    // 通过该接口设置 QPushButton 是一个无边框的按钮
    minButton->setFlat(true);
    // 设置最小化的图标和图标大小
    minButton->setIcon(QIcon(":/img/imgs/Minimize.png"));
    minButton->setIconSize(QSize(24, 24));

    QPushButton *closeButton = new QPushButton(this);
    closeButton->setFlat(true);
    closeButton->setIcon(QIcon(":/img/imgs/Close.png"));
    closeButton->setIconSize(QSize(24, 24));

    mainLayout->addWidget(searchEdit);
    mainLayout->addStretch();
    mainLayout->addWidget(minButton);
    mainLayout->addWidget(closeButton);
}
