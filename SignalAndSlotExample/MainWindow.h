#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAbstractButton;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void examConnection();
    void examOverloadConnection();

    void connectionBindLoop();
    void connectionBindNest();

signals:
    void customButtonClicked();

protected slots:
    void onPushButtonClicked();
    void onButtonGroupButtonClicked(QAbstractButton *);
    void onCustomButtonClicked();
    void onConnectionBindLoop();
    void onConnectionBindNest();
};
#endif // MAINWINDOW_H
