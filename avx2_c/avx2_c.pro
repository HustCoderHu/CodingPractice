TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    cal_p.c

QMAKE_CFLAGS += -mavx2

HEADERS += \
    cal_p.h
