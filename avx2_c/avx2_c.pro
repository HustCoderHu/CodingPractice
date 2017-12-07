TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    cal_p.c

HEADERS += \
    cal_p.h

QMAKE_CFLAGS += -mavx2
QMAKE_CFLAGS += -fopenmp
#QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -lgomp -lpthread
