#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <QStackedWidget>

class CarouselItem;
class CarouselTransition;
class CarouselItemContainer;
class CarouselGeometryAnimation;
class Carousel : public QStackedWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(Carousel)

public:
    Carousel(QWidget *parent = nullptr);
    ~Carousel();

    void setAutoScroll(bool autoScroll);
    bool autoScroll() const;

    void scrollNext();
    void scrollPrev();

    void setCurrentIndex(int index);
    int currentIndex() const;

    void addItem(CarouselItem *item);
    void removeItem(CarouselItem *item);

    void setTransition(CarouselTransition *transition);
    CarouselTransition *transition() const;

Q_SIGNALS:
    void currentIndexChanged(int index);
    void itemRemoved(int index);

private:
    int addWidget(QWidget *w);
    int insertWidget(int index, QWidget *w);
    void removeWidget(QWidget *w);
    QWidget *currentWidget() const;
    void appendRunningContainer(CarouselItemContainer *container);

private Q_SLOTS:
    void setCurrentWidget(QWidget *w);
    void clearIndexOnCarouselFinished();

private:
    QList<CarouselItem *> m_items;
    CarouselTransition *m_transition;
    CarouselGeometryAnimation *m_animation;
    QTimer *m_autoScroll;
    int m_currentIndex;
    QList<CarouselItemContainer *> m_runningContainers;
};
#endif // CAROUSEL_H
