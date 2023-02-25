#include "Dialog.h"
#include "Widget.h"

#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 0
    Widget w;
    // 调整窗口大小为 800x600
    w.resize(800,  600);
    w.move(100, 100);

    Widget w1(&w);
    // 调整窗口大小为 200x200
    w1.resize(200,  200);
    w1.move(100, 100);

    w.show();
    qDebug() << "WindowType: w: " << w.windowType() << "w1: " << w1.windowType();
#else
    Dialog dialog;

    dialog.resize(800, 600);
    dialog.show();
#endif
    return a.exec();
}
