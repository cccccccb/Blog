#include "TestCarouselWidget.h"
#include "carousel/Carousel.h"
#include "carousel/CarouselItem.h"
#include "carousel/CarouselTransition.h"

#include <QEasingCurve>
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QRadioButton>
#include <QButtonGroup>

class ImageCarouselItem : public CarouselItem
{
public:
    ImageCarouselItem(const QString &path)
        : m_path(path)
    {}

    void paint(QPainter *painter, const QRect &rect) override {
        painter->setRenderHint(QPainter::SmoothPixmapTransform);
        painter->drawImage(rect, QImage(m_path));
    }

private:
    QString m_path;
};

class CarouselHorizontalTransition : public CarouselTransition
{
public:
    using CarouselTransition::CarouselTransition;

    void preprocess(CarouselItem *prev, CarouselItem *next, const QRect &displayRect) override {
        if (prev) {
            prev->setStartRect(displayRect);
            prev->setEndRect(QRect(-displayRect.width(), 0, displayRect.width(), displayRect.height()));
        }

        if (next) {
            next->setStartRect(QRect(displayRect.width(), 0, displayRect.width(), displayRect.height()));
            next->setEndRect(displayRect);
        }
    }

    QRect interpolated(const QRect &from, const QRect &to, qreal progress) override {
        QEasingCurve curve(QEasingCurve::Linear);
        qreal value = curve.valueForProgress(progress);

        QRect result(from);
        result.setX(from.x() - qAbs(to.x() - from.x()) * value);
        result.setWidth(from.width());

        return result;
    }
};

class CarouselVerticalTransition : public CarouselTransition
{
public:
    using CarouselTransition::CarouselTransition;

    void preprocess(CarouselItem *prev, CarouselItem *next, const QRect &displayRect) override {
        if (prev) {
            prev->setStartRect(displayRect);
            prev->setEndRect(QRect(0, -displayRect.height(), displayRect.width(), displayRect.height()));
        }

        if (next) {
            next->setStartRect(QRect(0, displayRect.height(), displayRect.width(), displayRect.height()));
            next->setEndRect(displayRect);
        }
    }

    QRect interpolated(const QRect &from, const QRect &to, qreal progress) override {
        QEasingCurve curve(QEasingCurve::InQuart);
        qreal value = curve.valueForProgress(progress);

        QRect result(from);
        result.setY(result.y() - qAbs(to.y() - from.y()) * value);
        result.setHeight(from.height());

        return result;
    }
};

class CarouselMixedTransition : public CarouselTransition
{
public:
    using CarouselTransition::CarouselTransition;

    void preprocess(CarouselItem *prev, CarouselItem *next, const QRect &displayRect) override {
        if (prev) {
            prev->setStartRect(displayRect);

            prev->setEndRect(QRect(displayRect.width() / 4, -displayRect.height() / 2,
                                   displayRect.width() / 2, displayRect.height() / 2));
            prev->raise();
        }

        if (next) {
            next->setStartRect(displayRect);
            next->setEndRect(displayRect);
        }
    }

    QRect interpolated(const QRect &from, const QRect &to, qreal progress) override {
        if (to == from)
            return to;

        QRect result(from);
        QRect targetTmp({0, 0}, to.size());
        targetTmp.moveCenter(from.center());

        qreal p1Progress = 0.3;
        qreal p2Progress = 0.2;
        qreal p3Progress = 0.5;

        if (progress <= p1Progress) {
            qreal realProcess = progress / p1Progress;
            QEasingCurve curve(QEasingCurve::OutQuint);
            qreal value = curve.valueForProgress(realProcess);

            result.setWidth(from.width() - qAbs(targetTmp.width() - from.width()) * value);
            result.setHeight(from.height() - qAbs(targetTmp.height() - from.height()) * value);
            result.moveCenter(from.center());
        } else if (progress > p1Progress && progress <= p2Progress) {
            result = targetTmp;
        } else {
            qreal realProcess = (progress - (1 - p3Progress)) / p3Progress;
            QEasingCurve curve(QEasingCurve::InOutQuint);
            qreal value = curve.valueForProgress(realProcess);

            result.setX(targetTmp.x());
            result.setY(targetTmp.y() - qAbs(targetTmp.y() - to.y()) * value);
            result.setWidth(targetTmp.width());
            result.setHeight(targetTmp.height());
        }

        return result;
    }
};

TestCarouselWidget::TestCarouselWidget(QWidget *parent)
    : QWidget(parent)
{
    initUi();
}

void TestCarouselWidget::initUi()
{
    this->resize(800, 650);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout;
    mainLayout->addLayout(topLayout);

    Carousel *carousel1 = new Carousel(this);
    carousel1->setFixedSize(333, 255);
    topLayout->addWidget(carousel1, 0, Qt::AlignVCenter);

    carousel1->setTransition(new CarouselHorizontalTransition(this));
    carousel1->setAutoScroll(true);
    carousel1->addItem(new ImageCarouselItem(QLatin1String(":/res/Number1.png")));
    carousel1->addItem(new ImageCarouselItem(QLatin1String(":/res/Number2.png")));
    carousel1->addItem(new ImageCarouselItem(QLatin1String(":/res/Number3.png")));
    carousel1->addItem(new ImageCarouselItem(QLatin1String(":/res/Number4.png")));
    carousel1->addItem(new ImageCarouselItem(QLatin1String(":/res/Number5.png")));

    QWidget *carouselGroupWidget = new QWidget(this);
    QVBoxLayout *carouselGroupLayout = new QVBoxLayout(carouselGroupWidget);
    topLayout->addWidget(carouselGroupWidget, 0, Qt::AlignVCenter);

    Carousel *carousel2 = new Carousel(this);
    carousel2->setAutoScroll(true);
    carousel2->setFixedSize(333, 255);

    carousel2->setTransition(new CarouselVerticalTransition(this));
    carousel2->addItem(new ImageCarouselItem(QLatin1String(":/res/Number1.png")));
    carousel2->addItem(new ImageCarouselItem(QLatin1String(":/res/Number2.png")));
    carousel2->addItem(new ImageCarouselItem(QLatin1String(":/res/Number3.png")));
    carousel2->addItem(new ImageCarouselItem(QLatin1String(":/res/Number4.png")));
    carousel2->addItem(new ImageCarouselItem(QLatin1String(":/res/Number5.png")));

    QWidget *buttonWidget = new QWidget(carousel2);
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->setSpacing(10);

    QButtonGroup *buttonGroup = new QButtonGroup(this);
    for (int i = 0; i < carousel2->count(); ++i) {
        QRadioButton *radioButon = new QRadioButton(this);
        radioButon->setFixedSize(16, 16);
        radioButon->setStyleSheet("QRadioButton::indicator {"
                                  "image: url(:/res/radio.png);"
                                  "}"
                                  "QRadioButton::indicator:checked {"
                                  "image: url(:/res/radio_checked.png);"
                                  "}"
                                  );

        buttonGroup->addButton(radioButon, i);
        buttonLayout->addWidget(radioButon);
    }

    buttonGroup->button(0)->setChecked(true);
    connect(carousel2, &Carousel::currentIndexChanged, this, [buttonGroup](int index) {
        buttonGroup->button(index)->setChecked(true);
    });

    buttonWidget->ensurePolished();
    buttonWidget->move((carousel2->width() - buttonWidget->width()) / 2,
                       carousel2->rect().bottom() - buttonWidget->height());
    carouselGroupLayout->addWidget(carousel2, 0, Qt::AlignHCenter);

    Carousel *carousel3 = new Carousel(this);
    carousel3->setFixedSize(500, 320);
    mainLayout->addWidget(carousel3, 0, Qt::AlignHCenter);

    carousel3->setAutoScroll(true);
    carousel3->setTransition(new CarouselMixedTransition(this));
    carousel3->addItem(new ImageCarouselItem(QLatin1String(":/res/1.png")));
    carousel3->addItem(new ImageCarouselItem(QLatin1String(":/res/2.png")));
    carousel3->addItem(new ImageCarouselItem(QLatin1String(":/res/3.png")));
    carousel3->addItem(new ImageCarouselItem(QLatin1String(":/res/4.png")));
    carousel3->addItem(new ImageCarouselItem(QLatin1String(":/res/5.png")));
}
