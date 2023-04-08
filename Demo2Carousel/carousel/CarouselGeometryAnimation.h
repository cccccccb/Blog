#ifndef CAROUSELGEOMETRYANIMATION_H
#define CAROUSELGEOMETRYANIMATION_H

#include <QList>
#include <QRect>
#include <QVariantAnimation>

class CarouselItem;
class CarouselTransition;
class CarouselGeometryAnimation : public QVariantAnimation
{
    Q_OBJECT
public:
    CarouselGeometryAnimation(CarouselTransition *transition, QObject *parent = nullptr);

    void appendRunningItem(CarouselItem *item);

protected:
    QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const override;

private Q_SLOTS:
    void clearAndResetItemState();

private:
    struct AnimatedItem {
        CarouselItem *item = nullptr;
        qreal startProgress = 0.0;
        qreal progress = 0.0;
        QList<QRect> animatedStartRect;
        QList<QRect> animatedEndRect;
        int animatedRectIndex = -1;
    };

    QList<AnimatedItem *> m_runningItems;
    CarouselTransition *m_transition;
};

#endif // CAROUSELGEOMETRYANIMATION_H
