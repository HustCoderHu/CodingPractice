
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mylog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&dec_thread_, &DecoderThread::signal_on_avframe,
            this, &MainWindow::slots_on_avframe);
    dec_thread_.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slots_on_avframe(const AVFrame &frame)
{
    static int frame_id = 0;
    LOG << "frame_id:" << frame_id << " key:" << frame.key_frame
        << " :" << frame.pkt_dts << " :" << frame.pts;
    ++frame_id;
}


