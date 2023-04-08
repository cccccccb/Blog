#include "CarouselTransition.h"

CarouselTransition::CarouselTransition(QObject *parent)
    : QObject(parent)
{

}

quint32 CarouselTransition::duration() const
{
    return 1000;
}

void CarouselTransition::preprocess(CarouselItem *prev, CarouselItem *next, const QRect &displayRect)
{
    Q_UNUSED(prev);
    Q_UNUSED(next);
    Q_UNUSED(displayRect);
}
