TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    bitmap.cpp \
    clause.cpp \
    cnf.cpp \
    cnfedit.c

HEADERS += \
    bitmap.h \
    cnf.h \
    clause.h \
    cnfedit.h
