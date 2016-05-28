TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    wierzcholek.cpp \
    krawedz.cpp \
    graf.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    wierzcholek.h \
    krawedz.h \
    graf.h

