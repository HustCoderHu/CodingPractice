

解码线程
class DecodeThread {
slots:
  on_signal_exit();
  on_signal_suspend();
  on_frame_rendered(AVFrame* avframe);

signal:
  signal_frame_decoded(AVFrame* avframe);
  signal_last_framed_decoded(AVFrame* avframe);
}

class GLWidget {
slots:
  on_frame_decoded(AVFrame* avframe);      // 准备展示

signal:
  signal_frame_rendered(AVFrame* avframe); // 抛回解码线程复用
  
  uint32_t widget_idx_; // 位于下面 vector<GLWidget*> 的 index
  uint32_t frame_id_;   // 当前展示的 frame_id
  AVFrame* avframe_;
}

class ImagesWidget {
slots:
  on_frame_decoded(AVFrame* avframe);
// 网格展示多个 GLWidget
  vector<GLWidget*> glwidgets_; // size = 2^x
  // AVFrame *frame = glwidgets_[ frame_id % glwidgets_.size()]
  QGridLayout *layout_;
  
  map<uint32_t, AVFrame*> frames_map; // frame_id -> AVFrame*

  uint32_t grid_start_widget_id_;
  vector<uint32_t> displayed_frame_ids;
    
  // layout 第一个 widget 的 id
  // 滚动的时候此 id 会跟随变大 or 变小
  // layout 中的 widget 也会滚动
  // i.e. 当前显示 glwidgets_[1],[2],glwidgets_[3],4, 向后滚动 2 个, 就展示 3,4,5,6

  // AVFrame 由 glwidgets_[frame_id % glwidgets_.size()] 展示
}