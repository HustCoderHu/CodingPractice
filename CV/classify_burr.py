import numpy as np
import sys
import os
from pprint import pprint
import cv2 as cv
import json
# import heapq
from concurrent.futures import ProcessPoolExecutor
from concurrent.futures import ThreadPoolExecutor

cur_file_dir = os.path.abspath(sys.path[0])
sys.path.append(cur_file_dir)
import cv_boxes as cb
from myclassifier import MyClassifier

box_size = (30, 30)
stride_size = (5, 5)

# img_set_dir = r"E:\github_repo\img_set"
# img_set_dir = r"F:\PostGraduate\burr_det\train"
img_set_dir = r"D:\CV\original"
burr_dir = os.path.join(img_set_dir, "burr")
noburr_dir = os.path.join(img_set_dir, "noburr")

def cal_max(img_list):
  """
  cal max dot count of all imgs in img_list
  -> dict: img_path --> max_val
  :param img_list:
  :return:
  """
  future_dict = {}
  # max_workers = len(img_list)  # ThreadPoolExecutor
  max_workers = os.cpu_count()  # ProcessPoolExecutor
  # Process faster
  # ThreadPoolExecutor ProcessPoolExecutor
  with ProcessPoolExecutor(max_workers) as executor:
    for img_path in img_list:
      # args = (img_path, box_size, stride_size)
      future_dict[img_path] = \
        executor.submit(_scan_img, img_path, box_size, stride_size)
    executor.shutdown()
    # print("-------------------------------------")
  dict = {}
  for img_path, future_obj in future_dict.items():
    dict[img_path] = int(future_obj.result())
    # dict[img_path] = _scan_boxes(img_path, box_size, stride_size)
  # pprint(dict)
  return dict

def denoise_p_canny(img):
  img = cv.cvtColor(img, cv.COLOR_RGB2GRAY)
  # print(img.shape)

  # img = cv.bilateralFilter(img, 5, 50, 50)
  img_h, img_w = img.shape[:2]
  ratio = 0.17 # 2748 * 3840
  ratio = ratio * 2748 / 960 # 960 * 1280
  # img_h = int(img_h * ratio)
  # img_w = int(img_w * ratio)
  img = cv.resize(img, None, fx=ratio, fy=ratio, interpolation=cv.INTER_AREA)
  # print(img.shape)
  # blured = img
  # blured = cv.blur(img, (5, 5))
  # blured = cv.GaussianBlur(img, (5, 5), 0)
  img = cv.bilateralFilter(img, 7, 50, 50)
  canny = cv.Canny(img, 100, 50)
  return canny

def _scan_img(img_path, box_size, stride_size):
  """
  :param img_path:
  :param box_size: (box_h, box_w)
  :param stride: (stride_h, stride_w)
  :return: max sum among all boxes
  """
  img = cv.imread(img_path)
  canny = denoise_p_canny(img)
  # canny = cv.Canny(blured, 25, 75)
  feature = cb.pooling_sum(canny, box_size, stride_size)
  _max = cb.global_pooling_max(feature)
  return _max

def main(args):
  # img_list = ("19.jpg", "48.jpg", "1118.jpg", "1249.jpg")
  # img_list = ("1249.jpg",)

  # scan_all_burr()
  # scan_all_noburr()

  # show_mink_img(os.path.join(img_set_dir, "burr.json"))
  # show_max_img(os.path.join(img_set_dir, "noburr.json"))
  # cv.waitKey(0)

  test_predict()
  cv.destroyAllWindows()
  return

def scan_all_burr():
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
  return

def scan_all_noburr():
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
  return


def show_img_with_boxes(img_path, _k, box_size, stride_size):
  """
  :param img_path:
  :param box_size:
  :param stride_size:
  :param k: get max k  sum and boxes location
  :return:
  """
  img = cv.imread(img_path)
  canny = denoise_p_canny(img)
  # canny = cv.Canny(blured, 25, 75)
  # print(canny.shape)
  feature = cb.pooling_sum(canny, box_size, stride_size)
  # file = os.path.abspath("np.txt")
  # print(file)
  # file = os.path.join(img_set_dir, "np.txt")
  # np.savetxt(file, feature, fmt='%d')

  box_list = cb.maxk_boxes(feature, _k, box_size, stride_size)
  print(box_list)
  to_show = cb.draw_box_on_img(canny, box_list)

  winname = img_path
  cv.namedWindow(winname, cv.WINDOW_NORMAL | cv.WINDOW_KEEPRATIO)
  cv.imshow(winname, to_show)
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
    show_img_with_boxes(file, 3, box_size, stride_size)
  return

def show_mink_img(json_file):
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
    show_img_with_boxes(file, 3, box_size, stride_size)
  return

def predict(img_path, threshold):
  img = cv.imread(img_path)
  canny = denoise_p_canny(img)
  feature = cb.pooling_sum(canny, box_size, stride_size)
  _max = cb.global_pooling_max(feature)
  # print("box_sum: {}".format(_max))
  return _max, _max > threshold

def test_predict():
  global noburr_dir
  burr_min = 21420
  noburr_max = 19890
  threshold = (burr_min + noburr_max) / 2
  print("threshold: {}".format(threshold))
  print("-------------------------------------")
  img_path = os.path.join(noburr_dir, "a18.jpg")
  # print(predict(img_path, threshold))
  mycls = MyClassifier()
  max_sum, pred = mycls.predict(img_path)
  print(max_sum, pred)

  return

  img_set_dir = r"D:\CV\jpg"
  burr_dir = os.path.join(img_set_dir, "burr")
  noburr_dir = os.path.join(img_set_dir, "noburr")

  # burr
  flist = os.listdir(burr_dir)
  img_list = [os.path.join(burr_dir, file) for file in flist]
  max_dict_burr = cal_max(img_list)
  error_count = 0
  err_dict = {}
  for img_path, box_sum in max_dict_burr.items():
    print("{}: {}".format(img_path, box_sum))
    if box_sum <= threshold:
      err_dict[img_path] = box_sum
      error_count += 1

  print("error: ")
  pprint(err_dict)
  print("-------------------------------------")

  # noburr
  flist = os.listdir(noburr_dir)
  img_list = [os.path.join(noburr_dir, file) for file in flist]
  max_dict_noburr = cal_max(img_list)
  error_count = 0
  err_dict = {}
  for img_path, box_sum in max_dict_noburr.items():
    print("{}: {}".format(img_path, box_sum))
    if box_sum >= threshold:
      err_dict[img_path] = box_sum
      error_count += 1
  print("error: ")
  pprint(err_dict)
  print("-------------------------------------")

  # show_img_with_boxes(img_path, 1, box_size, stride_size)
  # cv.waitKey(0)

if __name__ == '__main__':

  main("")


# reference
# heapq min max k
# <http://python3-cookbook.readthedocs.io/zh_CN/latest/c01/p04_find_largest_or_smallest_n_items.html>
#