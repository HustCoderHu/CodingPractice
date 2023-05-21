#include <stddef.h>
#include <sstream>
#include "avframes_manager.h"
#include "mylog.h"

extern "C" {
#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
}

using std::ostringstream;

AVFramesManager::AVFramesManager() {}

void AVFramesManager::Reserve(uint32_t n)
{
  if (n <= free_frames_.size())
    return;

  if (n > max_alloc_frames_ - cur_alloc_frames_) {
    n = max_alloc_frames_ - cur_alloc_frames_;
  }
  AVFrame* frame = NULL;
  for (uint32_t i = 0; i < n; ++i, ++cur_alloc_frames_) {
    frame = av_frame_alloc();
    if (!frame) {
      LOG << "alloc frames failed, cur: " << cur_alloc_frames_
          << " max: " << max_alloc_frames_
          << " ENOMEM: " << ENOMEM;
      return;
    }
    free_frames_.push_back(frame);
  }
}

AVFrame* AVFramesManager::GetDecoded(uint32_t& frame_id)
{
  if (decoded_frames_.empty())
    return NULL;
  auto itr = decoded_frames_.begin();
  frame_id = itr->first;
  AVFrame *frame = itr->second;
  decoded_frames_.erase(itr);
  return frame;
}

void AVFramesManager::PutDecoded(AVFrame* frame)
{
  decoded_frames_.emplace(frame_id_++, frame);
  return;
}

AVFrame* AVFramesManager::GetFree()
{
  if (cur_alloc_frames_ == max_alloc_frames_) {
    LOG << "already alloc max frames: " << max_alloc_frames_;
    return NULL;
  }
  if (free_frames_.empty()) {
    AVFrame *frame = av_frame_alloc();
    if (!frame) {
      LOG << "alloc frames failed, cur: " << cur_alloc_frames_
          << " max: " << max_alloc_frames_
          << " ENOMEM: " << ENOMEM;
      return NULL;
    }
    ++cur_alloc_frames_;
    free_frames_.push_back(frame);
    return frame;
  }
  AVFrame *frame = free_frames_.back();
  free_frames_.pop_back();
  return frame;
}

void AVFramesManager::PutFree(AVFrame* frame)
{
  free_frames_.push_back(frame);
}

string AVFramesManager::Stat()
{
  ostringstream os;
  os << "decoded:" << decoded_frames_.size()
     << " free:" << free_frames_.size()
     << " cur_alloc:" << cur_alloc_frames_
     << " max:" << max_alloc_frames_;
  return os.str();
}
