#ifndef RIGHTMAINWIDGET_H
#define RIGHTMAINWIDGET_H

#include <QWidget>

class RightMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RightMainWidget(QWidget *parent = nullptr);

protected:
    void initUi();

    void initCentralWidget(QWidget *centralWidget);
};

#endif // RIGHTMAINWIDGET_H
