
#ifndef MYDECODER_H
#define MYDECODER_H

#include <QThread>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

class DecoderThread : public QThread
{
  Q_OBJECT

public:
  DecoderThread();

  void run() override;

  int output_video_frame(AVFrame *frame);

  int decode_packet(AVCodecContext *dec, const AVPacket *pkt);

  int hw_decoder_init(AVCodecContext *ctx, const enum AVHWDeviceType type);
  int open_codec_context(int *stream_idx, AVCodecContext **codec_ctx, enum AVMediaType type);
  int get_format_from_sample_fmt(const char **fmt, enum AVSampleFormat sample_fmt);

  AVFormatContext *fmt_ctx_ = NULL;
  AVCodecContext *video_codec_ctx_ = NULL; // audio

  int width_, height_;

  AVPixelFormat pix_fmt_;
  AVPixelFormat hw_pix_fmt_;

  AVStream *video_stream_ = NULL; // audio
  int video_stream_idx_ = -1;

  bool hw_decode_ = false;
  AVBufferRef *hw_device_ctx_ = NULL;
signals:
  void signal_on_avframe(AVFrame *frame);
};

#endif // MYDECODER_H
