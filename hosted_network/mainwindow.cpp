#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "thread"
//#include <QProcess>

//#define WIN32_LEAN_AND_MEAN
//#include <stdio.h>
//#include <windows.h>
//#include <winnt.h>

//#include "winsock2.h"
//#include "windows.h"
//#include "wlanapi.h"
//#include "iphlpapi.h"

//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "IPHLPAPI.lib"
//#pragma comment(lib, "wlanapi.lib")


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    WlanMain = new Mywlan;
    if(NULL == WlanMain) {
//        QDebug() << error;
    }
}

MainWindow::~MainWindow()
{
    delete WlanMain;
    delete ui;
}
