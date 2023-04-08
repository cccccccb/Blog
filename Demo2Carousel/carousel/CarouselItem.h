#ifndef CAROUSELITEM_H
#define CAROUSELITEM_H

#include <QRect>

class QWidget;
class QPainter;
class CarouselItem
{
    friend class Carousel;
    friend class CarouselGeometryAnimation;
public:
    CarouselItem();

    void setStartRect(const QRect &rect);
    QRect startRect() const;

    void setEndRect(const QRect &rect);
    QRect endRect() const;

    void setVisible(bool visible);
    bool isVisible() const;

    void raise();
    void lower();

    int index() const;

    virtual void paint(QPainter *painter, const QRect &rect) = 0;

private:
    void setWidget(QWidget *w);
    QWidget *widget() const;

private:
    QRect m_startRect;
    QRect m_endRect;

    QWidget *m_bindWidget;
};

#endif // CAROUSELITEM_H
