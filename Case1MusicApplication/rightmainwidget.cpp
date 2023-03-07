#include "playbackbar.h"
#include "rightmainwidget.h"
#include "titlebar.h"

#include <QLabel>
#include <QVBoxLayout>

RightMainWidget::RightMainWidget(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("RightMainWidget");
    initUi();
}

void RightMainWidget::initUi()
{
    // 将布局移至单独的界面完成，外部无需管理其填充方式
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 创建主布局，并设置到当前界面中，同时将其添加到对象树上。
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    // 调整主布局的间距和边距为 0
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    // 创建标题栏控件并添加到对象树中
    TitleBar *titleBar = new TitleBar(this);

    // 创建中心主界面区域
    QWidget *centralWidget = new QWidget(this);
    initCentralWidget(centralWidget);

    // 创建播放栏区域
    PlaybackBar *playbackBar = new PlaybackBar(this);

    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(centralWidget);
    mainLayout->addWidget(playbackBar);
}

void RightMainWidget::initCentralWidget(QWidget *centralWidget)
{
    // 水平布局用于添加文本和图片
    QHBoxLayout *layout = new QHBoxLayout(centralWidget);
    // 去掉布局中的边距和间距
    layout->setMargin(0);
    layout->setSpacing(0);

    // 添加布局的文本和图片
    QLabel *centralWidgetTextLabel = new QLabel(this);
    centralWidgetTextLabel->setText("搜我所想~~");

    QLabel *centralWidgetImageLabel = new QLabel(this);
    centralWidgetImageLabel->setPixmap(QPixmap(":/img/imgs/HappyFace.png"));

    // 水平方向放置两个弹簧互相挤压里面的控件，使其相邻并居中
    layout->addStretch();
    layout->addWidget(centralWidgetTextLabel);
    layout->addWidget(centralWidgetImageLabel);
    layout->addStretch();
}
