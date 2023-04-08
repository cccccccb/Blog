#include "CarouselItem.h"

#include <QStackedWidget>
#include <QWidget>

CarouselItem::CarouselItem()
{

}

void CarouselItem::setStartRect(const QRect &rect)
{
    if (m_startRect == rect)
        return;

    m_startRect = rect;
}

QRect CarouselItem::startRect() const
{
    return m_startRect;
}

void CarouselItem::setEndRect(const QRect &rect)
{
    if (m_endRect == rect)
        return;

    m_endRect = rect;
}

QRect CarouselItem::endRect() const
{
    return m_endRect;
}

void CarouselItem::setVisible(bool visible)
{
    m_bindWidget->setVisible(visible);
}

bool CarouselItem::isVisible() const
{
    return m_bindWidget->isVisible();
}

void CarouselItem::raise()
{
    m_bindWidget->raise();
}

void CarouselItem::lower()
{
    m_bindWidget->lower();
}

int CarouselItem::index() const
{
    if (QStackedWidget *stackedWidget = qobject_cast<QStackedWidget *>(m_bindWidget->parentWidget())) {
        return stackedWidget->indexOf(m_bindWidget);
    }

    return -1;
}

void CarouselItem::setWidget(QWidget *w)
{
    m_bindWidget = w;
}

QWidget *CarouselItem::widget() const
{
    return m_bindWidget;
}

