
#ifndef MYDECODER_H
#define MYDECODER_H

#include <vector>
#include <map>

#include <QThread>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

#include "avframes_manager.h"

using std::vector;
using std::map;

class DecoderThread : public QObject
{
  Q_OBJECT

public:
  DecoderThread();

  void set_video_file(const char* file) { video_file_ = file; }
  void Init(const char* file);

  int output_video_frame(AVFrame *frame);

  int decode_packet(AVCodecContext *dec, const AVPacket *pkt);

  int hw_decoder_init(AVCodecContext *ctx, const enum AVHWDeviceType type);
  int open_codec_context(int *stream_idx, AVCodecContext **codec_ctx, enum AVMediaType type);
  int get_format_from_sample_fmt(const char **fmt, enum AVSampleFormat sample_fmt);

private:
  uint32_t emit_frames(uint32_t n);
  uint32_t decode_and_cache(uint32_t max_cache);

public slots:
  void on_require_frames(uint32_t n);
  void on_frame_consumed(AVFrame* avframe);
  void on_timer();
  void on_signal_suspend() { }
  void on_signal_exit();

signals:
  void signal_frame_decoded(uint32_t frame_id, AVFrame *avframe);
  void signal_last_frame_decoded(AVFrame *avframe);
  void signal_all_frames_decoded();

private:
  const char* video_file_ = nullptr;

  AVFramesManager avframes_mgr;
  uint32_t max_cache_decoded_frames_ = 30 * 2;
  // 1. if (! free_frames_.empty)
  //       frame = free_frames_.pop_back();
  // 2. decode(AVCodecContext*, frame);
  // 3. decoded_frames_.emplace({frame_id++, frame});

  AVFormatContext *fmt_ctx_ = NULL;
  AVCodecContext *video_codec_ctx_ = NULL; // audio

  int width_, height_;

  AVPixelFormat pix_fmt_;
  AVPixelFormat hw_pix_fmt_;

  AVStream *video_stream_ = NULL; // audio
  int video_stream_idx_ = -1;

  bool hw_decode_ = false;
  AVBufferRef *hw_device_ctx_ = NULL;

  AVPacket *avpacket_ = NULL;
};

#endif // MYDECODER_H
