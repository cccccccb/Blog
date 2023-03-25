#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QAbstractButton;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void displayGroupBoxContainer();
    void displaySplitterContainer();
    void displayFrameContainer();
    void displayScrollAreaContainer();
    void displayStackedWidgetContainer();
    void displayTabWidgetContainer();

protected slots:
    void onDisplayButtonGroupClicked(QAbstractButton *button);
};
#endif // WIDGET_H
