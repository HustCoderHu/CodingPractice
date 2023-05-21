#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "images_panel.h"

#include "mylog.h"

Q_DECLARE_METATYPE(AVFrame)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  img_panel_ = new ImagesPanel(this);
//  glwidget_ = new GLWidget;

//  QGridLayout *mainLayout = new QGridLayout;
//  mainLayout->addWidget(glwidget_, 0, 0);
//  setLayout(mainLayout);
//  connect(glwidget_, &GLWidget::signal_on_avframe, glwidget_, &GLWidget::repaint);
//  connect(&dec_thread_, &DecoderThread::signal_on_avframe, this, &MainWindow::slots_on_avframe);
//  dec_thread_.start();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::ShowImgPanel()
{
  img_panel_->InitGLWidgets();
  img_panel_->PutLayout();
  img_panel_->resize(1600, 900);
  img_panel_->setWindowTitle("image_panel");
  img_panel_->show();
//  img_panel_->showFullScreen();
}

//void MainWindow::resizeEvent(QResizeEvent*)
//{
////  glwidget_->setMinimumSize(0, 0);
//}

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
//  emit glwidget_->signal_on_avframe(frame);
}
