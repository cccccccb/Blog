#ifndef TESTCAROUSELWIDGET_H
#define TESTCAROUSELWIDGET_H

#include <QWidget>

class TestCarouselWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TestCarouselWidget(QWidget *parent = nullptr);

protected:
    void initUi();
};

#endif // TESTCAROUSELWIDGET_H
