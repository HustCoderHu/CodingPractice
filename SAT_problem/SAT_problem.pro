TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
    clause.cpp \
    cnf.cpp \
    solver.cpp \
    version.cpp \
    bitmap.cpp \
    versionset.cpp \
    versionedit.cpp \
    vsetbuilder.cpp

HEADERS += \
    _clause.h \
    _cnf.h \
    clause.h \
    cnf.h \
    solver.h \
    version.h \
    bitmap.h \
    versionset.h \
    versionedit.h \
    vsetbuilder.h
