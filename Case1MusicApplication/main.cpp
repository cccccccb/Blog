#include "applicationwindow.h"

#include <QApplication>
#include <QFile>

QByteArray loadQSSFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly))
        return "";

    return file.readAll();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ApplicationWindow w;
    w.setStyleSheet(loadQSSFile(":/qss/applicationwindow.qss"));

    w.show();
    return a.exec();
}
