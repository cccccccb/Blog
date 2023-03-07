#ifndef LEFTNAVIGATIONWIDGET_H
#define LEFTNAVIGATIONWIDGET_H

#include <QWidget>

class LeftNavigationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftNavigationWidget(QWidget *parent = nullptr);

protected:
    void initUi();
};

#endif // LEFTNAVIGATIONWIDGET_H
