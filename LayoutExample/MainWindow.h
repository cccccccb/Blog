#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QHBoxLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayMarginAndSpacing(QHBoxLayout *mainLayout);
    void displayStretch(QHBoxLayout *mainLayout);
    void displayStretchFactor(QHBoxLayout *mainLayout);
    void displaySizePolicy(QHBoxLayout *);
    void displaySizePolicyStretch(QHBoxLayout *);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
