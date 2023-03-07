#include "playbackbar.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>

PlaybackBar::PlaybackBar(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("PlaybackBar");
    initUi();
}

void PlaybackBar::initUi()
{
    // 调整当前控件的大小策略并设置固定高度
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(60);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(10);

    QLabel *playbackLabel = new QLabel(this);
    playbackLabel->setAlignment(Qt::AlignCenter);
    playbackLabel->setPixmap(QPixmap(":/img/imgs/PlaybackIcon.png"));
    playbackLabel->setFixedSize(48, 48);

    // 创建音乐信息的布局，包含音乐的名称和进度
    // 这里没有添加到对象树中，后续会通过 addLayout 添加进去。
    QVBoxLayout *musicInfoLayout = new QVBoxLayout;
    // 设置布局的边距和间距
    musicInfoLayout->setMargin(0);
    musicInfoLayout->setSpacing(4);

    // 创建歌曲名称的 label
    QLabel *musicNameLabel = new QLabel(this);
    // 设置默认显示的文本，一般情况下不进行设置会通过接口获取，这里为了演示界面而进行的设置
    musicNameLabel->setText("雨还是不停地下 - 孙燕姿");
    // 添加到布局中
    musicInfoLayout->addWidget(musicNameLabel);

    // QSlider 是一个滑块控件，这个控件可以用来代替歌曲的进度条
    QSlider *musicPositionSlider = new QSlider(this);
    // 设置滑动条的方向
    musicPositionSlider->setOrientation(Qt::Horizontal);
    // 设置滑动的范围为 0 - 100
    musicPositionSlider->setRange(0, 100);
    // 设置滑块的默认值为 45
    musicPositionSlider->setValue(45);
    // 添加到布局中
    musicInfoLayout->addWidget(musicPositionSlider);

    // 添加歌曲位置的文本，并添加到当前对象树中
    QLabel *musicPositonLabel = new QLabel(this);
    // 设置歌曲文本的对齐方式为右对齐
    musicPositonLabel->setAlignment(Qt::AlignRight);
    musicPositonLabel->setText("00:00 / 04:51");
    // 添加到布局中
    musicInfoLayout->addWidget(musicPositonLabel);

    // 创建控制按钮组的布局器
    QHBoxLayout *controlMusicLayout = new QHBoxLayout;
    // 设置布局器的边距和间距
    controlMusicLayout->setMargin(0);
    controlMusicLayout->setSpacing(5);

    // 创建上一首按钮
    QPushButton *previousButton = new QPushButton(this);
    previousButton->setIcon(QIcon(":/img/imgs/PlayerPrevious.png"));
    previousButton->setIconSize(QSize(24, 24));
    controlMusicLayout->addWidget(previousButton);

    // 创建播放按钮
    QPushButton *playButton = new QPushButton(this);
    playButton->setIcon(QIcon(":/img/imgs/PlayerPlay.png"));
    playButton->setIconSize(QSize(24, 24));
    controlMusicLayout->addWidget(playButton);

    // 创建下一首按钮
    QPushButton *nextButton = new QPushButton(this);
    nextButton->setIcon(QIcon(":/img/imgs/PlayerNext.png"));
    nextButton->setIconSize(QSize(24, 24));
    controlMusicLayout->addWidget(nextButton);

    // 添加各控件到布局中
    mainLayout->addWidget(playbackLabel);
    // 歌曲信息的布局需要填充整个空余位置
    mainLayout->addLayout(musicInfoLayout, 1);
    mainLayout->addLayout(controlMusicLayout);

}
