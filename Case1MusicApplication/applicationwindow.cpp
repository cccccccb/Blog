#include "applicationwindow.h"
#include "leftnavigationwidget.h"
#include "rightmainwidget.h"

#include <QHBoxLayout>

extern QByteArray loadQSSFile(const QString &fileName);

ApplicationWindow::ApplicationWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowOpacity(0.9);

    initUi();
}

ApplicationWindow::~ApplicationWindow()
{
}

void ApplicationWindow::initUi()
{
    // 初始化应用程序的大小
    this->resize(800, 600);
    // 创建主布局，并设置到当前界面中，同时添加到当前的对象树上。
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName("ApplicationCentralWidget");
    mainLayout->addWidget(centralWidget);

    QHBoxLayout *centralLayout = new QHBoxLayout(centralWidget);
    centralLayout->setSpacing(0);

    // 创建左侧导航栏控件，并添加到当前对象树中。
    LeftNavigationWidget *leftNavigationWidget = new LeftNavigationWidget(this);
    // 创建右侧中心界面，并添加到当前对象树中。
    RightMainWidget *rightCentralWidget = new RightMainWidget(this);

    // 将这些控件添加到主界面的布局中
    centralLayout->addWidget(leftNavigationWidget);
    centralLayout->addWidget(rightCentralWidget);
}
