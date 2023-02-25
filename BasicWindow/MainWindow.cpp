#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addCustomMenuInMenuBar();
    addCustomToolBar();

    addCustomStatusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addCustomActionInMenuBar()
{
    // 创建菜单栏，并增加到对象树中
    QMenuBar *menuBar = new QMenuBar(this);

    // 增加三个菜单栏动作
    menuBar->addAction("Menu1");
    menuBar->addAction("Menu2");
    menuBar->addAction("Menu3");

    this->setMenuBar(menuBar);
}

void MainWindow::addCustomMenuInMenuBar()
{
    // 创建菜单栏，并增加到对象树中
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *menu = new QMenu("菜单1");
    // 增加三个菜单动作到菜单中
    menu->addAction("子菜单1");
    menu->addAction("子菜单2");
    menu->addAction("子菜单3");

    // 菜单也能添加子菜单作为某个选项的多种不同选择
    QMenu *subMenu = new QMenu("某个选项的子菜单", this);
    subMenu->addAction("选项子菜单1");
    subMenu->addAction("选项子菜单2");
    subMenu->addAction("选项子菜单3");

    // 添加子菜单到菜单中
    menu->addMenu(subMenu);

    // 将菜单添加到菜单栏中
    menuBar->addMenu(menu);

    this->setMenuBar(menuBar);
}

void MainWindow::addCustomToolBar()
{
    // 循环添加 5 个状态栏
    for (int i = 0; i < 5; ++i) {
        QToolBar *toolBar = new QToolBar(this);
        for (int j = 0; j < 4; ++j) {
            // 循环为每个状态栏添加4个动作
            toolBar->addAction(QString("工具栏动作") + QString::number(i*4+j+1));
        }

        // 我们将工具栏放置到主窗口的左侧
        this->addToolBar(Qt::LeftToolBarArea, toolBar);
    }
}

void MainWindow::addCustomStatusBar()
{
    // 用于显示消息
    statusBar()->showMessage("这是状态栏中显示的消息");
    // 将自定义文本永久的设置到状态栏中
    statusBar()->addPermanentWidget(new QLabel("这是自定义文本"));
}

