// http://ffmpeg.org/doxygen/trunk/decode_video_8c-example.html
// http://ffmpeg.org/doxygen/trunk/demux_decode_8c-example.html
// http://ffmpeg.org/doxygen/trunk/hw_decode_8c-example.html

extern "C" {

#include <libavutil/imgutils.h>
#include <libavutil/samplefmt.h>
#include <libavutil/timestamp.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>

}

#include "decoder_thread.h"

#include "mylog.h"

#define __STDC_CONSTANT_MACROS

static const char *src_filename = NULL;

static uint8_t *video_dst_data[4] = {NULL};
static int video_dst_linesize[4];
static int video_dst_bufsize;

static AVFrame *frame = NULL;
static AVPacket *pkt = NULL;
static int video_frame_count = 0;

int DecoderThread::output_video_frame(AVFrame *frame)
{
    if (frame->width != width_ || frame->height != height_ ||
        frame->format != pix_fmt_) {
        /* To handle this change, one could call av_image_alloc again and
         * decode the following frames into another rawvideo file. */
//        LOG << "Error: Width, height and pixel format have to be "
//            << "constant in a rawvideo file, but the width, height or "
//            << "pixel format of the input video changed:";
//        LOG << "old: width=" << width_ << ", height=" << height_
//            << ", format=" << av_get_pix_fmt_name(pix_fmt_);
//        LOG << "new: width=" << frame->width << ", height=" << frame->height
//            << ", format=" << av_get_pix_fmt_name((AVPixelFormat)frame->format);
        //        return -1;
    }

    LOG << "video frame n:" << video_frame_count++;
    //    printf("video_frame n:%d\n", video_frame_count++);
    return 0;

    /* copy decoded frame to destination buffer:
     * this is required since rawvideo expects non aligned data */
    av_image_copy(video_dst_data, video_dst_linesize,
                  (const uint8_t **)(frame->data), frame->linesize,
                  pix_fmt_, width_, height_);

    /* write to rawvideo file */
    //    fwrite(video_dst_data[0], 1, video_dst_bufsize, video_dst_file);
    return 0;
}

int DecoderThread::decode_packet(AVCodecContext *dec, const AVPacket *pkt)
{
    int ret = 0;
    char av_err_str[AV_ERROR_MAX_STRING_SIZE];

    AVFrame *sw_frame = NULL;

    // submit the packet to the decoder
    ret = avcodec_send_packet(dec, pkt);
    if (ret < 0) {
        av_make_error_string(av_err_str, AV_ERROR_MAX_STRING_SIZE, ret);
        fprintf(stderr, "Error submitting a packet for decoding (%s)\n", av_err_str);
        return ret;
    }

    // get all the available frames from the decoder
    while (ret >= 0) {
        ret = avcodec_receive_frame(dec, frame);
        if (ret < 0) {
            // those two return values are special and mean there is no output
            // frame available, but there were no errors during decoding
            if (ret == AVERROR_EOF || ret == AVERROR(EAGAIN))
                return 0;

            av_make_error_string(av_err_str, AV_ERROR_MAX_STRING_SIZE, ret);
            fprintf(stderr, "Error during decoding (%s)\n", av_err_str);
            return ret;
        }

        // write the frame data to output file
        if (dec->codec->type == AVMEDIA_TYPE_VIDEO) {
            emit signal_on_avframe(*frame);
            ret = output_video_frame(frame);

            if (false && hw_decode_ && frame->format == hw_pix_fmt_) {
                // retrieve data from GPU to CPU
                LOG << "video_frame_count:" << video_frame_count;
                if ((ret = av_hwframe_transfer_data(sw_frame, frame, 0)) < 0) {
                    fprintf(stderr, "Error transferring the data to system memory\n");
                    goto fail;
                }
            }
//            av_hwframe_transfer_data();
        }
//        av_frame_unref(frame);
    }
fail:
//    av_frame_unref(frame);
    return 0;
}

int DecoderThread::hw_decoder_init(AVCodecContext *ctx, const enum AVHWDeviceType type)
{
    int err = 0;

    if ((err = av_hwdevice_ctx_create(&hw_device_ctx_, type,
                                      NULL, NULL, 0)) < 0) {
        fprintf(stderr, "Failed to create specified HW device.\n");
        return err;
    }
    ctx->hw_device_ctx = av_buffer_ref(hw_device_ctx_);

    return err;
}

int DecoderThread::open_codec_context(int *stream_idx,
                                      AVCodecContext **codec_ctx,
                                      enum AVMediaType type)
{
    int ret, stream_index;
    AVStream *avstream;
    const AVCodec *avcodec = NULL;

    AVHWDeviceType device_type;
    if (hw_decode_)
        device_type = av_hwdevice_find_type_by_name("dxva2");

    ret = av_find_best_stream(fmt_ctx_, type, -1, -1, NULL, 0);
    if (ret < 0) {
        fprintf(stderr, "Could not find %s stream in input file '%s'\n",
                av_get_media_type_string(type), src_filename);
        return ret;
    } else {
        stream_index = ret;
        avstream = fmt_ctx_->streams[stream_index];


        /* find decoder for the stream */
        avcodec = avcodec_find_decoder(avstream->codecpar->codec_id);
        //        dec = avcodec_find_decoder_by_name("dxva2");
        if (!avcodec) {
            fprintf(stderr, "Failed to find %s codec\n",
                    av_get_media_type_string(type));
            return AVERROR(EINVAL);
        }

        if (hw_decode_) {
            int index = 0;
            for (index = 0; ;++index) {
                const AVCodecHWConfig *config = avcodec_get_hw_config(avcodec, index);
                if (NULL == config) {
                    LOG << "avcodec_get_hw_config failed, index:" << index;
                }
                if (!config) {
                    LOG << "Decoder [" << avcodec->name << "]"
                        << " does not support device type:"
                        << av_hwdevice_get_type_name(device_type);
                }
                if (config->methods & AV_CODEC_HW_CONFIG_METHOD_HW_DEVICE_CTX &&
                    config->device_type == device_type) {
                    hw_pix_fmt_ = config->pix_fmt;
                    LOG << " found break";
                    break;
                }
            }
        }

        /* Allocate a codec context for the decoder */
        *codec_ctx = avcodec_alloc_context3(avcodec);
        if (!*codec_ctx) {
            fprintf(stderr, "Failed to allocate the %s codec context\n",
                    av_get_media_type_string(type));
            return AVERROR(ENOMEM);
        }

        /* Copy codec parameters from input stream to output codec context */
        if ((ret = avcodec_parameters_to_context(*codec_ctx, avstream->codecpar)) < 0) {
            fprintf(stderr, "Failed to copy %s codec parameters to decoder context\n",
                    av_get_media_type_string(type));
            return ret;
        }

        if (hw_decode_) {
            if (hw_decoder_init(*codec_ctx, device_type) < 0) {
                LOG << "hw_decoder_init < 0";
                return -1;
            }
        }

        /* Init the decoders */
        if ((ret = avcodec_open2(*codec_ctx, avcodec, NULL)) < 0) {
            fprintf(stderr, "Failed to open %s codec\n",
                    av_get_media_type_string(type));
            return ret;
        }
        *stream_idx = stream_index;
    }

    return 0;
}

int DecoderThread::get_format_from_sample_fmt(const char **fmt,
                                              enum AVSampleFormat sample_fmt)
{
    int i;
    struct sample_fmt_entry {
        enum AVSampleFormat sample_fmt; const char *fmt_be, *fmt_le;
    } sample_fmt_entries[] = {
                              { AV_SAMPLE_FMT_U8,  "u8",    "u8"    },
                              { AV_SAMPLE_FMT_S16, "s16be", "s16le" },
                              { AV_SAMPLE_FMT_S32, "s32be", "s32le" },
                              { AV_SAMPLE_FMT_FLT, "f32be", "f32le" },
                              { AV_SAMPLE_FMT_DBL, "f64be", "f64le" },
                              };
    *fmt = NULL;

    for (i = 0; i < FF_ARRAY_ELEMS(sample_fmt_entries); i++) {
        struct sample_fmt_entry *entry = &sample_fmt_entries[i];
        if (sample_fmt == entry->sample_fmt) {
            *fmt = AV_NE(entry->fmt_be, entry->fmt_le);
            return 0;
        }
    }

    fprintf(stderr,
            "sample format %s is not supported as output format\n",
            av_get_sample_fmt_name(sample_fmt));
    return -1;
}

DecoderThread::DecoderThread()
{

}

void DecoderThread::run()
{
    int ret = 0;

    int argc = 4;
    char *argv[] = {};
    if (argc != 4) {
        fprintf(stderr, "usage: %s  input_file video_output_file audio_output_file\n"
                        "API example program to show how to read frames from an input file.\n"
                        "This program reads frames from a file, decodes them, and writes decoded\n"
                        "video frames to a rawvideo file named video_output_file, and decoded\n"
                        "audio frames to a rawaudio file named audio_output_file.\n",
                argv[0]);
        exit(1);
    }
    src_filename = "Z:/coding/github/steins_gate_cut.mkv";
    src_filename = "D:/docs/movie/.unknown/6798973.mp4";
    //    video_dst_filename = "Z:/coding/github/steins_gate_cut.video";
    //    audio_dst_filename = "Z:/coding/github/steins_gate_cut.audio";
    //    src_filename = argv[1];
    //    video_dst_filename = argv[2];
    //    audio_dst_filename = argv[3];

    /* open input file, and allocate format context */
    if (avformat_open_input(&fmt_ctx_, src_filename, NULL, NULL) < 0) {
        fprintf(stderr, "Could not open source file %s\n", src_filename);
        exit(1);
    }

    /* retrieve stream information */
    if (avformat_find_stream_info(fmt_ctx_, NULL) < 0) {
        fprintf(stderr, "Could not find stream information\n");
        exit(1);
    }

    LOG << "open open_codec_context video";
    if (open_codec_context(&video_stream_idx_, &video_codec_ctx_, AVMEDIA_TYPE_VIDEO) >= 0) {
        video_stream_ = fmt_ctx_->streams[video_stream_idx_];

        //        video_dst_file = fopen(video_dst_filename, "wb");
        //        if (!video_dst_file) {
        //            fprintf(stderr, "Could not open destination file %s\n", video_dst_filename);
        //            ret = 1;
        //            goto end;
        //        }

        /* allocate image where the decoded image will be put */
        width_ = video_codec_ctx_->width;
        height_ = video_codec_ctx_->height;
        pix_fmt_ = video_codec_ctx_->pix_fmt;
        ret = av_image_alloc(video_dst_data, video_dst_linesize,
                             width_, height_, pix_fmt_, 1);
        if (ret < 0) {
            fprintf(stderr, "Could not allocate raw video buffer\n");
            goto end;
        }
        video_dst_bufsize = ret;
    }

    /* dump input information to stderr */
    //    av_dump_format(fmt_ctx_, 0, src_filename, 0);

    if (!video_stream_) {
        fprintf(stderr, "Could not find video stream in the input, aborting\n");
        ret = 1;
        goto end;
    }

    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate frame\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    pkt = av_packet_alloc();
    if (!pkt) {
        fprintf(stderr, "Could not allocate packet\n");
        ret = AVERROR(ENOMEM);
        goto end;
    }

    //    if (video_stream_)
    //        printf("Demuxing video from file '%s' into '%s'\n", src_filename, video_dst_filename);

    /* read frames from the file */
    while (av_read_frame(fmt_ctx_, pkt) >= 0) {
        // check if the packet belongs to a stream we are interested in, otherwise
        // skip it
        if (pkt->stream_index == video_stream_idx_)
            ret = decode_packet(video_codec_ctx_, pkt);

        av_packet_unref(pkt);
        if (ret < 0)
            break;
    }

    /* flush the decoders */
    if (video_codec_ctx_)
        decode_packet(video_codec_ctx_, NULL);

    printf("Demuxing succeeded.\n");

//    if (video_stream_) {
//        printf("Play the output video file with the command:\n"
//               "ffplay -f rawvideo -pix_fmt %s -video_size %dx%d %s\n",
//               av_get_pix_fmt_name(pix_fmt_), width_, height_,
//               video_dst_filename);
//    }

end:
    avcodec_free_context(&video_codec_ctx_);
    avformat_close_input(&fmt_ctx_);
    //    if (video_dst_file)
    //        fclose(video_dst_file);
    av_packet_free(&pkt);
    av_frame_free(&frame);
    av_free(video_dst_data[0]);

    LOG << "ret:" << ret;
}

