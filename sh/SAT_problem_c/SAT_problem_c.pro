TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    bitmap.cpp \
    clause.cpp

HEADERS += \
    bitmap.h \
    cnf.h \
    clause.h
