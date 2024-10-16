TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        complementario.cpp \
        estacion.cpp \
        main.cpp \
        red.cpp \
        surtidor.cpp \
        venta.cpp

HEADERS += \
    complementario.h \
    estacion.h \
    red.h \
    surtidor.h \
    venta.h

DISTFILES += \
    baseDatos
