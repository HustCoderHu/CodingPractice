import numpy as np
import sys
import os
from pprint import pprint
import cv2 as cv
import json
# import heapq
from concurrent.futures import ProcessPoolExecutor
from concurrent.futures import ThreadPoolExecutor

# cur_file_dir = os.path.abspath(sys.path[0])
# sys.path.append(cur_file_dir)
import cv_boxes as cb

class MyClassifier:
  resize_ratio = 0.17  # 2748 * 3840
  kernel_size = [30, 30]
  stride_size = [5, 5]
  sum_threshold = 20655
  # global_pooling_max = lambda img: np.max(img)

  # def __init__(self):
    # self.ratio = 0.17 # 2748 * 3840
    # self.box_size = [30, 30]
    # self.stride_size = [5, 5]
  def predict(self, img_path):
    img = cv.imread(img_path)
    print("ddd")
    canny = self.denoise_p_canny(img)
    print("aaa")
    feature = self.pooling_sum(img)
    print("bbb")
    global_pooling_max = lambda img: np.max(img)
    max_sum = global_pooling_max(feature)
    print("ccc")
    return max_sum, max_sum >= self.sum_threshold

  def denoise_p_canny(self, img):
    _img = cv.cvtColor(img, cv.COLOR_RGB2GRAY)
    # print(img.shape)
    # img = cv.bilateralFilter(img, 5, 50, 50)
    img_h, img_w = _img.shape[:2]
    # ratio = 0.17  # 2748 * 3840
    # ratio = ratio * 2748 / 960  # 960 * 1280
    # img_h = int(img_h * ratio)
    # img_w = int(img_w * ratio)
    ratio_ = (img_h * img_w / (2748 * 3840)) ** 0.5
    print(ratio_)
    ratio_ *= self.resize_ratio
    print(ratio_)
    _img = cv.resize(_img, None, fx=ratio_,
                     fy=ratio_, interpolation=cv.INTER_AREA)
    # print(img.shape)
    # blured = img
    # blured = cv.blur(img, (5, 5))
    # blured = cv.GaussianBlur(img, (5, 5), 0)
    _img = cv.bilateralFilter(_img, 7, 50, 50)
    canny = cv.Canny(_img, 100, 50)
    return canny

  def pooling_sum(self, img):
    img_h, img_w = img.shape[:2]
    knl_h, knl_w = self.kernel_size
    strd_h, strd_w = self.stride_size

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

  def topk_boxes_on_img(self, img_path, _k):
    img = cv.imread(img_path)
    canny = self.denoise_p_canny(img)
    feature = self.pooling_sum(img)
    box_list = self.topk_boxes(feature, _k)
    img = self.draw_box_on_img(canny, box_list)

    return img

  def topk_boxes(self, _array, _k):
    knl_h, knl_w = self.kernel_size
    strd_h, strd_w = self.stride_size
    box_list = []  # element [left, top, right, bottom, box_sum]
    to_2d_pos = lambda x, strd: (int(x / strd), int(x % strd))
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

  def draw_box_on_img(self, img, box_list):
    # img, text, org, fontFace, fontScale, color, thickness=None, lineType=None, bottomLeftOrigin=None
    font = cv.FONT_HERSHEY_SIMPLEX
    if img.ndim < 3 or img.shape[2] < 3:
      img = cv.cvtColor(img, cv.COLOR_GRAY2RGB)
    # print(img.shape)

    # winname = "aaa"
    # cv.namedWindow(winname, cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
    for box in box_list:
      left, top, right, bottom, box_sum = box
      box_sum = int(box_sum)
      # print(box_sum)
      # print(box)
      cv.rectangle(img, (left, top), (right, bottom), (0, 255, 0), 1)

      # cv.imshow(winname, img)
      # cv.waitKey(0)
      cv.putText(img, str(box_sum), (left, top), font, 1, (0, 0, 255), 1)
      # cv.imshow(winname, img)
      # cv.waitKey(0)
      # img = cv.putText(img, str(box_sum), (left, top), font, 50, (0, 255, 0), 20)
    return img