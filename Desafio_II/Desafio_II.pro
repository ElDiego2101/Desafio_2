TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        estacion.cpp \
        main.cpp \
        red.cpp \
        surtidor.cpp \
        venta.cpp

HEADERS += \
    estacion.h \
    red.h \
    surtidor.h \
    venta.h
