#ifndef CAROUSELTRANSITION_H
#define CAROUSELTRANSITION_H

#include <QObject>

class CarouselItem;
class CarouselTransition : public QObject
{
    Q_OBJECT    

public:
    explicit CarouselTransition(QObject *parent = nullptr);

    virtual quint32 duration() const;
    virtual void preprocess(CarouselItem *prev, CarouselItem *next, const QRect &displayRect);
    virtual QRect interpolated(const QRect &from, const QRect &to, qreal progress) = 0;
};

#endif // CAROUSELTRANSITION_H
