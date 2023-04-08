#include <QApplication>

#include "TestCarouselWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TestCarouselWidget w;
    w.show();

    return a.exec();
}
