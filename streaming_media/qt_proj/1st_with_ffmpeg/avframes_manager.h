
#pragma once

#include <stdint.h>
#include <vector>
#include <map>
#include <string>

using std::string;
using std::vector;
using std::map;

class AVFrame;

class AVFramesManager
{
public:
  AVFramesManager();

  void Reserve(uint32_t n);

  size_t DecodedFrames() { return decoded_frames_.size(); }
  AVFrame* GetDecoded(uint32_t& frame_id);
  void PutDecoded(AVFrame* frame);

  AVFrame* GetFree();
  void PutFree(AVFrame *frame);

  string Stat();

  map<uint32_t, AVFrame*> decoded_frames_; // frameid -> AVFrame*
//  map<uint32_t, AVFrame*>
  vector<AVFrame*> free_frames_;
  uint32_t max_alloc_frames_ = 30 * 20;
  uint32_t cur_alloc_frames_ = 0;

  uint32_t frame_id_ = 0;
};

