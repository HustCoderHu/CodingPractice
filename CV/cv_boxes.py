import numpy as np
# import sys
# import os
# from pprint import pprint
import cv2 as cv
# import json
# import heapq

def pooling_sum(img, knl_size, stride_size):
  img_h, img_w = img.shape[:2]
  knl_h, knl_w = knl_size
  strd_h, strd_w = stride_size

  out_h = int((img_h - knl_h) / strd_h) + 1
  out_w = int((img_w - knl_w) / strd_w) + 1
  out = np.zeros((out_h, out_w), dtype=np.int64)
  cur_h = 0
  for _h in range(out_h):
    cur_w = 0
    for _w in range(out_w):
      out[_h, _w] = np.sum(
        img[cur_h:cur_h + knl_h, cur_w:cur_w + knl_w])
      cur_w += strd_w
    cur_h += strd_h
  return out

def global_pooling_max(img):
  return np.max(img)

def maxk_boxes(_array, _k, knl_size, stride_size):
  knl_h, knl_w = knl_size
  strd_h, strd_w = stride_size
  box_list = []  # element [left, top, right, bottom, box_sum]
  to_2d_pos = lambda x, strd: (int(x / strd), int(x % strd))

  # _arr = _array.copy()
  # print(_array.shape)
  # print(np.size(_array))
  for _ in range(_k):
    # print(_)
    flat_idx = _array.argmax()
    # print(flat_idx)
    _h, _w = to_2d_pos(flat_idx, _array.shape[1])
    top = _h * strd_h
    left = _w * strd_w
    right = left + knl_w
    bottom = top + knl_h
    val = _array[_h, _w]
    box_list.append([left, top, right, bottom, val])
    # set max to zero  to find all max k
    _array[_h, _w] = 0

  return box_list

def draw_box_on_img(img, box_list):
  # img, text, org, fontFace, fontScale, color, thickness=None, lineType=None, bottomLeftOrigin=None
  font = cv.FONT_HERSHEY_SIMPLEX
  if img.ndim < 3 or img.shape[2] < 3:
    img = cv.cvtColor(img, cv.COLOR_GRAY2RGB)
  # print(img.shape)

  # winname = "aaa"
  # cv.namedWindow(winname, cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
  for box in box_list:
    left, top, right, bottom, box_sum = box
    box_sum = int(box_sum/255)
    # print(box_sum)
    # print(box)
    cv.rectangle(img, (left, top), (right, bottom), (0, 255, 0), 1)

    # cv.imshow(winname, img)
    # cv.waitKey(0)
    cv.putText(img, str(box_sum), (left, top), font, 1, (0,0,255), 1)
    # cv.imshow(winname, img)
    # cv.waitKey(0)
    # img = cv.putText(img, str(box_sum), (left, top), font, 50, (0, 255, 0), 20)
  return img