#include "leftnavigationwidget.h"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>

LeftNavigationWidget::LeftNavigationWidget(QWidget *parent)
    : QWidget(parent)
{
    initUi();
}

QToolButton * createToolButton(const QString &text, const QString &iconName)
{
    QToolButton *toolButton = new QToolButton;

    toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    toolButton->setFixedHeight(70);
    toolButton->setText(text);
    toolButton->setIcon(QIcon(iconName));
    toolButton->setIconSize(QSize(48, 48));

    return toolButton;
}

void LeftNavigationWidget::initUi()
{
    // 指定固定宽度，防止左侧导航栏出现挤压到最小大小的情况。
    this->setFixedWidth(70);

    // 创建一个垂直布局并设置到当前界面中中
    QVBoxLayout *leftNavigationLayout = new QVBoxLayout(this);
    // 设置布局的间距为 0
    leftNavigationLayout->setSpacing(0);
    // 设置布局的边距为0
    leftNavigationLayout->setMargin(0);

    // 创建一个存储图标的 label 控件
    QLabel *iconLabel = new QLabel(this);
    // 添加 iconLabel 的图片资源
    iconLabel->setPixmap(QPixmap(":/img/imgs/MusicIcon.png"));
    // 设置 Label 的水平居中
    iconLabel->setAlignment(Qt::AlignHCenter);
    // 将图标的大小策略修改为，水平填充，竖直固定。
    // 由于左侧导航栏固定了宽度，这里的水平填充其实就是保持和左侧导航栏一样宽度。
    iconLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // 设置图标控件的宽度为固定 50
    iconLabel->setFixedHeight(50);

    // 创建按钮组, 用于管理按钮的选中状态
    QButtonGroup *leftNavigationButtonGroup = new QButtonGroup(this);

    QToolButton *searchButton = createToolButton("搜索", ":/img/imgs/Collection.png");
    leftNavigationButtonGroup->addButton(searchButton);
    // 设置搜索按钮为选中状态
    searchButton->setCheckable(true);
    searchButton->setChecked(true);

    QToolButton *musicListButton = createToolButton("歌单", ":/img/imgs/MusicList.png");
    leftNavigationButtonGroup->addButton(musicListButton);

    QToolButton *rankListButton = createToolButton("排行榜", ":/img/imgs/RankList.png");
    leftNavigationButtonGroup->addButton(rankListButton);

    QToolButton *collectionButton = createToolButton("收藏", ":/img/imgs/Collection.png");
    leftNavigationButtonGroup->addButton(collectionButton);

    QToolButton *settingsButton = createToolButton("设置", ":/img/imgs/Settings.png");
    leftNavigationButtonGroup->addButton(settingsButton);

    // 添加控件到布局中
    leftNavigationLayout->addWidget(iconLabel);
    leftNavigationLayout->addWidget(searchButton);
    leftNavigationLayout->addWidget(musicListButton);
    leftNavigationLayout->addWidget(rankListButton);
    leftNavigationLayout->addWidget(collectionButton);
    leftNavigationLayout->addWidget(settingsButton);
    leftNavigationLayout->addStretch();
}
