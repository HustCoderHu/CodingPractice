
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "decoder_thread.h"

#include <QMainWindow>
extern "C" {
#include <libavcodec/avcodec.h>
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slots_on_avframe(const AVFrame& frame);

private:
    Ui::MainWindow *ui;

    DecoderThread dec_thread_;
};

#endif // MAINWINDOW_H
