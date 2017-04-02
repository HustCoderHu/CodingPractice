#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T12:28:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hosted_network
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mywlan.cpp \
    service_opt/serviceop.cpp

HEADERS  += mainwindow.h \
    mywlan.h \
    service_opt/serviceop.h

#    fuvk_headers/eaptypes.h \
#    fuvk_headers/l2cmn.h \
#    fuvk_headers/windot11.h \
#    fuvk_headers/wlanapi.h

FORMS    += mainwindow.ui

INCLUDEPATH += ./
INCLUDEPATH += service_opt/

#LIBS	+= -L ./wlan_lib/ -lws2_32
#LIBS	+= -L ./wlan_lib/ -lwlanapi
#LIBS	+= -L ./wlan_lib/ -lIPHLPAPI
