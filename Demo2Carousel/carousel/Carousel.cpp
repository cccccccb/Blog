#include "Carousel.h"
#include "CarouselItem.h"
#include "CarouselTransition.h"
#include "CarouselGeometryAnimation.h"

#include <QPainter>
#include <QTimer>
#include <QVariantAnimation>
#include <QDebug>

class CarouselItemContainer : public QWidget
{
public:
    explicit CarouselItemContainer(QWidget *parent = nullptr);

    void setItem(CarouselItem *item);
    CarouselItem *item() const;

private:
    void paintEvent(QPaintEvent *event);

private:
    CarouselItem *m_item;
};

CarouselItemContainer::CarouselItemContainer(QWidget *parent)
    : QWidget(parent)
    , m_item(nullptr)
{

}

void CarouselItemContainer::setItem(CarouselItem *item)
{
    Q_ASSERT(!m_item);

    m_item = item;
}

CarouselItem *CarouselItemContainer::item() const
{
    return m_item;
}

void CarouselItemContainer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    m_item->paint(&painter, this->rect());

    return QWidget::paintEvent(event);
}

Carousel::Carousel(QWidget *parent)
    : QStackedWidget(parent)
    , m_transition(nullptr)
    , m_animation(nullptr)
    , m_autoScroll(nullptr)
    , m_currentIndex(-1)
{
}

Carousel::~Carousel()
{
    qDeleteAll(m_items);
    m_items.clear();
}

void Carousel::setAutoScroll(bool autoScroll)
{
    if (autoScroll) {
        if (!m_autoScroll) {
            m_autoScroll = new QTimer(this);
            m_autoScroll->callOnTimeout([this]() {
                scrollNext();
            });
        }

        if (m_transition)
            m_autoScroll->start(m_transition->duration() + 2000);
        else
            m_autoScroll->start(2000);
    } else {
        if (m_autoScroll) {
            m_autoScroll->deleteLater();
            m_autoScroll = nullptr;
        }
    }
}

bool Carousel::autoScroll() const
{
    return m_autoScroll;
}

void Carousel::scrollNext()
{
    int nextIndexAround = currentIndex() + 1;
    int nextIndex = nextIndexAround >= count() ? 0 : nextIndexAround;
    setCurrentIndex(nextIndex);
}

void Carousel::scrollPrev()
{
    int prevIndexAround = currentIndex() - 1;
    int prevIndex = prevIndexAround < 0 ? count() - 1 : prevIndexAround;
    setCurrentIndex(prevIndex);
}

void Carousel::setCurrentIndex(int index)
{
    if (index >= count()) {
        index = count() - 1;
    } else if (index < 0) {
        index = 0;
    }

    if (!m_transition) {
        if (QWidget *cw = currentWidget())
            cw->setGeometry(0, 0, this->width(), this->height());

        if (index == currentIndex())
            return;

        m_currentIndex = index;
        QStackedWidget::setCurrentIndex(index);
        Q_EMIT currentIndexChanged(index);
        return;
    }

    if (CarouselItemContainer *currentItenContainer = dynamic_cast<CarouselItemContainer *>(currentWidget())) {
        CarouselItemContainer *nextConatiner = dynamic_cast<CarouselItemContainer *>(widget(index));
        if (nextConatiner == currentItenContainer)
            return;

        if (!m_animation) {
            m_animation = new CarouselGeometryAnimation(m_transition, this);
            QObject::connect(m_animation, &CarouselGeometryAnimation::finished, this, &Carousel::clearIndexOnCarouselFinished);

            m_animation->setStartValue(0);
            m_animation->setEndValue(100);
        }

        m_animation->setDuration(m_transition->duration());
        m_transition->preprocess(currentItenContainer->item(), nextConatiner->item(), this->rect());

        appendRunningContainer(currentItenContainer);
        appendRunningContainer(nextConatiner);

        if (m_animation->state() == CarouselGeometryAnimation::Running)
            m_animation->stop();

        m_animation->start();
        m_currentIndex = index;
        Q_EMIT currentChanged(index);
    }
}

int Carousel::currentIndex() const
{
    return m_currentIndex;
}

void Carousel::addItem(CarouselItem *item)
{
    if (m_items.contains(item))
        return;

    CarouselItemContainer *container = new CarouselItemContainer(this);
    container->setItem(item);
    item->setWidget(container);
    m_items.append(item);

    if (m_currentIndex == -1)
        m_currentIndex = 0;

    QStackedWidget::addWidget(container);
}

void Carousel::removeItem(CarouselItem *item)
{
    if (!m_items.contains(item))
        return;

    m_items.removeOne(item);

    if (m_items.isEmpty())
        m_currentIndex = -1;

    QStackedWidget::removeWidget(item->widget());
}

void Carousel::setTransition(CarouselTransition *transition)
{
    if (m_transition) {
        delete m_transition;
    }

    m_transition = transition;
    if (m_transition && m_autoScroll && m_autoScroll->isActive())
        m_autoScroll->start(m_transition->duration() + 2000);
}

CarouselTransition *Carousel::transition() const
{
    return m_transition;
}

int Carousel::addWidget(QWidget *w)
{
    return QStackedWidget::addWidget(w);
}

int Carousel::insertWidget(int index, QWidget *w)
{
    return QStackedWidget::insertWidget(index, w);
}

void Carousel::removeWidget(QWidget *w)
{
    return QStackedWidget::removeWidget(w);
}

QWidget *Carousel::currentWidget() const
{
    return widget(m_currentIndex);
}

void Carousel::appendRunningContainer(CarouselItemContainer *container)
{
    if (!container->isVisible())
        container->setVisible(true);

    m_runningContainers.append(container);
    m_animation->appendRunningItem(container->item());
}

void Carousel::setCurrentWidget(QWidget *w)
{
    return QStackedWidget::setCurrentWidget(w);
}

void Carousel::clearIndexOnCarouselFinished()
{
    int ci = currentIndex();
    QStackedWidget::setCurrentIndex(ci);
    for (CarouselItemContainer *container : qAsConst(m_runningContainers)) {
        container->lower();
        if (currentWidget() == container)
            continue;

        container->setVisible(false);
    }

    m_runningContainers.clear();
    Q_EMIT currentIndexChanged(ci);
}
