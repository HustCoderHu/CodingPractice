TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    clause.cpp \
    cnf.cpp \
    solver.cpp

HEADERS += \
    _clause.h \
    _cnf.h \
    clause.h \
    cnf.h \
    solver.h
