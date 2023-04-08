QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

include(carousel/carousel.pri)

SOURCES += \
    TestCarouselWidget.cpp \
    main.cpp \

HEADERS += \
    TestCarouselWidget.h

RESOURCES += \
    images.qrc

