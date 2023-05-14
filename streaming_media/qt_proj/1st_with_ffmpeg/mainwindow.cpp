
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mylog.h"

Q_DECLARE_METATYPE(AVFrame)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  glwidget_ = new GLWidget;

  connect(glwidget_, &GLWidget::signal_on_avframe, glwidget_, &GLWidget::repaint);

  connect(&dec_thread_, &DecoderThread::signal_on_avframe, this, &MainWindow::slots_on_avframe);
  dec_thread_.start();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::slots_on_avframe(AVFrame* frame)
{
  static int frame_id = 0;
  LOG << "frame_id:" << frame_id
      << " key:" << frame->key_frame
      << " " << frame->width << '*' << frame->height
      << " dts:" << frame->pkt_dts << " :"
      << frame->pts;
  ++frame_id;

//  glwidget_->repaint(frame);
  emit glwidget_->signal_on_avframe(frame);
}
