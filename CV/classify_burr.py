import numpy as np
# import sys
import os
from pprint import pprint
import cv2 as cv
import json
from concurrent.futures import ProcessPoolExecutor
from concurrent.futures import ThreadPoolExecutor


def cal_max(img_list):
  """
  cal max dot count of all imgs in img_list
  -> dict: img_path --> max_val
  :param img_list:
  :return:
  """
  box_size = (200, 200)
  stride_size = (100, 100)

  future_dict = {}
  # max_workers = len(img_list)  # ThreadPoolExecutor
  max_workers = os.cpu_count()  # ProcessPoolExecutor
  # Process faster
  # ThreadPoolExecutor ProcessPoolExecutor
  with ProcessPoolExecutor(max_workers) as executor:
    for img_path in img_list:
      args = (img_path, box_size, stride_size)
      future_dict[img_path] = \
        executor.submit(_scan_boxes, img_path, box_size, stride_size)
    executor.shutdown()
    print("-------------------------------------")
  dict = {}
  for img_path, future_obj in future_dict.items():
    dict[img_path] = int(future_obj.result())
    # dict[img_path] = _scan_boxes(img_path, box_size, stride_size)
  # pprint(dict)
  return dict

def _scan_boxes(img_path, box_size, stride_size):
  """
  :param img_path:
  :param box_size: (box_h, box_w)
  :param stride: (stride_h, stride_w)
  :return: max sum among all boxes
  """
  img = cv.imread(img_path)
  img = cv.cvtColor(img, cv.COLOR_RGB2GRAY)
  # blured = cv.blur(img, (5, 5))
  blured = cv.GaussianBlur(img, (51, 51), 0)
  # blured = img
  canny = cv.Canny(blured, 25, 75)
  # canny = cv.Canny(blured, 25, 75)
  img_h = canny.shape[0]
  img_w = canny.shape[1]
  box_h, box_w = box_size
  stride_h, stride_w = stride_size
  sum_h = int((img_h - box_h) / stride_h) + 1
  sum_w = int((img_w - box_w) / stride_w) + 1
  sum_arr = np.zeros((sum_h, sum_w), dtype=np.int64)

  tmp_h = 0
  for _h in range(sum_h):
    tmp_w = 0
    for _w in range(sum_w):
      sum_arr[_h, _w] = np.sum(
        canny[tmp_h:tmp_h + box_h, tmp_w:tmp_w + box_w] )
      tmp_w += stride_w
    tmp_h += stride_h

  return sum_arr.max()

def show_edges(img_path, winname):
  """
  :param img_path:
  :return:
  """
  img = cv.imread(img_path)
  img = cv.cvtColor(img, cv.COLOR_RGB2GRAY)
  # blured = cv.blur(img, (51, 51))
  blured = cv.GaussianBlur(img, (17, 17), 0)
  # blured = img

  # cv.resizeWindow("blured", 600, 400)
  # cv.imshow("blured", blured)
  canny = cv.Canny(blured, 25, 75)

  # print(type(canny))
  cv.namedWindow(winname, cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
  cv.resizeWindow(winname, 1000, 700)
  cv.imshow(winname, canny)
  cv.waitKey(0)
  cv.destroyAllWindows()
  # canny.tofile(img_path + ".txt", sep = " ")
  # print(canny.sum())
  return

def show_max_img(json_file):
  with open(json_file, "r") as f:
    _dict = json.load(f)

  max_sum = max(_dict.values())
  img_list = []
  for img_path, val in _dict.items():
    if val == max_sum:
      img_list.append(img_path)
  # print(img_list)

  for file in img_list:
    print("max: {} -> {}".format(max_sum, file))
    # print(os.path.exists(file))
    show_edges(file, file)
  return

def show_min_img(json_file):
  with open(json_file, "r") as f:
    _dict = json.load(f)

  max_sum = min(_dict.values())
  img_list = []
  for img_path, val in _dict.items():
    if val == max_sum:
      img_list.append(img_path)
  # print(img_list)

  for file in img_list:
    print("min: {} -> {}".format(max_sum, file))
    # print(os.path.exists(file))
    show_edges(file, file)
  return

def main(args):
  # img_list = ("19.jpg", "48.jpg", "1118.jpg", "1249.jpg")
  # img_list = ("1249.jpg",)
  img_set_dir = r"E:\github_repo\img_set"
  img_set_dir = r"F:\PostGraduate\burr_det\train"
  burr_dir = os.path.join(img_set_dir, "burr")
  noburr_dir = os.path.join(img_set_dir, "noburr")

  show_min_img(os.path.join(img_set_dir, "burr.json"))
  # show_max_img(os.path.join(img_set_dir, "noburr.json"))
  return

  img_list = []
  flist = os.listdir(burr_dir)
  for file in flist:
    if os.path.splitext(file)[1] != ".jpg":
      continue
    img_list.append(os.path.join(burr_dir, file))
  max_dict_burr = cal_max(img_list)
  img_list.clear()
  burr_min = min(max_dict_burr.values())
  print(burr_min)
  # dump to file
  json_file = os.path.join(img_set_dir, "burr.json")
  with open(json_file, "w") as f:
    json.dump(max_dict_burr, f)
  print("--- dict dump to file: {}".format(json_file))
  # return

  img_list = []
  flist = os.listdir(noburr_dir)
  for file in flist:
    if os.path.splitext(file)[1] != ".jpg":
      continue
    img_list.append(os.path.join(noburr_dir, file))
  max_dict_noburr = cal_max(img_list)
  noburr_max = max(max_dict_noburr.values())
  print(noburr_max)
  # dump to file
  json_file = os.path.join(img_set_dir, "noburr.json")
  with open(json_file, "w") as f:
    json.dump(max_dict_noburr, f)
  print("--- dict dump to file: {}".format(json_file))

  # pprint(max_dict_burr)
  # for img_path in img_list:
  #   show_edges(img_path, img_path)

  # cv.waitKey(0)
  # cv.destroyAllWindows()
  return

if __name__ == '__main__':
  main("")
