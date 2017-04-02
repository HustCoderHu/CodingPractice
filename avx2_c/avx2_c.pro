TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    cal_p.c

HEADERS += \
    cal_p.h

QMAKE_CFLAGS += -mavx2
