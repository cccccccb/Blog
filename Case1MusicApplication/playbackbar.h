#ifndef PLAYBACKBAR_H
#define PLAYBACKBAR_H

#include <QWidget>

class PlaybackBar : public QWidget
{
    Q_OBJECT
public:
    explicit PlaybackBar(QWidget *parent = nullptr);

protected:
    void initUi();
};

#endif // PLAYBACKBAR_H
