#include "CarouselGeometryAnimation.h"
#include "CarouselItem.h"
#include "CarouselTransition.h"

#include <QWidget>
#include <QDebug>

CarouselGeometryAnimation::CarouselGeometryAnimation(CarouselTransition *transition, QObject *parent)
    : QVariantAnimation(parent)
    , m_transition(transition)
{
    QObject::connect(this, &QVariantAnimation::finished, this, &CarouselGeometryAnimation::clearAndResetItemState);
}

void CarouselGeometryAnimation::appendRunningItem(CarouselItem *item)
{
    auto it = std::find_if(m_runningItems.cbegin(), m_runningItems.cend(),
                 [item](AnimatedItem *animatedItem) {
        return animatedItem->item == item;
    });

    if (it != m_runningItems.cend()) {
        (*it)->animatedStartRect.append(item->startRect());
        (*it)->animatedEndRect.append(item->endRect());
        return;
    }

    AnimatedItem *animatedItem = new AnimatedItem();
    animatedItem->item = item;
    animatedItem->progress = 0.0;
    animatedItem->animatedStartRect = {item->startRect()};
    animatedItem->animatedEndRect = {item->endRect()};
    animatedItem->animatedRectIndex = 0;
    m_runningItems.append(animatedItem);
}

QVariant CarouselGeometryAnimation::interpolated(const QVariant &from, const QVariant &to, qreal progress) const
{
    for (AnimatedItem * const animatedItem : qAsConst(m_runningItems)) {
        if (qFuzzyIsNull(progress))
            animatedItem->startProgress = animatedItem->progress;

        if (animatedItem->progress > 1.0) {
            int animatedRectIndex = (animatedItem->animatedRectIndex + 1);
            if (animatedRectIndex >= animatedItem->animatedStartRect.count()
                    || animatedRectIndex >= animatedItem->animatedEndRect.count())
                continue;

            animatedItem->startProgress = -progress;
            animatedItem->animatedRectIndex = animatedRectIndex;
        }

        animatedItem->progress = animatedItem->startProgress + progress;
        QRect rect = m_transition->interpolated(animatedItem->animatedStartRect[animatedItem->animatedRectIndex],
                animatedItem->animatedEndRect[animatedItem->animatedRectIndex], animatedItem->progress);
        animatedItem->item->widget()->setGeometry(rect);
    }

    return QVariantAnimation::interpolated(from, to, progress);
}

void CarouselGeometryAnimation::clearAndResetItemState()
{
    qDeleteAll(m_runningItems);
    m_runningItems.clear();
}

