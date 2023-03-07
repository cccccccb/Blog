#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QWidget>

class ApplicationWindow : public QWidget
{
    Q_OBJECT

public:
    ApplicationWindow(QWidget *parent = nullptr);
    ~ApplicationWindow();

protected:
    void initUi();
};
#endif // APPLICATIONWINDOW_H
