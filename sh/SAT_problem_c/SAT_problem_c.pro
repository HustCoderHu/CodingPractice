TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c11

SOURCES += main.c \
    bitmap.c \
    clause.c \
    cnf.c \
    cnfedit.c \
    solver.c

HEADERS += \
    bitmap.h \
    clause.h \
    cnf.h \
    cnfedit.h \
    solver.h
