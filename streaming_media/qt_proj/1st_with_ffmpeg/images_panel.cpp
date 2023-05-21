#include <QTimer>
#include "images_panel.h"
#include "mylog.h"

ImagesPanel::ImagesPanel(QWidget *parent)
    : QWidget{parent}
{
  const char* file = "D:/docs/movie/.unknown/6798973.mp4";
  dec_obj_ = new DecoderThread;
  dec_obj_->Init(file);
  dec_obj_->moveToThread(&dec_thread_);
  dec_thread_.start();

  connect(&dec_thread_, &QThread::finished, dec_obj_, &QObject::deleteLater);
  connect(this, &ImagesPanel::signal_require_frames,
          dec_obj_, &DecoderThread::on_require_frames);
  connect(dec_obj_, &DecoderThread::signal_frame_decoded,
          this, &ImagesPanel::on_frame_decoded);
  connect(this, &ImagesPanel::signal_frame_consumed,
          dec_obj_, &DecoderThread::on_frame_consumed);

  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, dec_obj_, &DecoderThread::on_timer);
  connect(timer_, &QTimer::timeout, this, &ImagesPanel::on_timer);
  timer_->start(1000);
}

void ImagesPanel::InitGLWidgets()
{
  uint32_t max_glwidgets = 16;

  for (uint32_t i = 0; i < max_glwidgets; ++i) {
    GLWidget *glw = new GLWidget;
    glwidgets_.push_back(glw);
  }
}

void ImagesPanel::PutLayout()
{
  if (!layout_)
    layout_ = new QGridLayout;

  uint32_t n_row = 4;
  uint32_t n_col = 4;
  uint32_t glw_idx = 0;
  for (uint32_t row = 0; row < n_row; ++row) {
    for (uint32_t col = 0; col < n_col; ++col) {
      layout_->addWidget(glwidgets_[glw_idx++], row, col);
    }
  }
  setLayout(layout_);
}

void ImagesPanel::on_frame_decoded(uint32_t frame_id, AVFrame* avframe)
{
  LOG << "fid: " << frame_id
      << " key:" << avframe->key_frame
      << " pts:" << avframe->pkt_pos
      << " " << avframe->width << "*" << avframe->height
      << " " << avframe;
  frames_map.emplace(frame_id, avframe);
  uint32_t glw_idx = frame_id % glwidgets_.size();
  glwidgets_[glw_idx]->repaint(avframe);
    emit signal_frame_consumed(avframe);
}

void ImagesPanel::on_timer()
{
    emit signal_require_frames(4*4);
}


