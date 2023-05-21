
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "decoder_thread.h"
//#include "glwidget.h"

#include <QMainWindow>
extern "C" {
#include <libavcodec/avcodec.h>
}


class ImagesPanel;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void ShowImgPanel();

//  void resizeEvent(QResizeEvent *);

public slots:
  void slots_on_avframe(AVFrame *frame);

private:
  Ui::MainWindow *ui;

  ImagesPanel *img_panel_;

//  DecoderThread dec_thread_;
//  GLWidget *glwidget_;
};

#endif // MAINWINDOW_H
