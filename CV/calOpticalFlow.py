# 基于Python的OpenCV图像处理17
# <http://zhaoxuhui.top/blog/2017/06/28/%E5%9F%BA%E4%BA%8EPython%E7%9A%84OpenCV%E5%9B%BE%E5%83%8F%E5%A4%84%E7%90%8617.html>

import cv2 as cv
import numpy as np
import os
import os.path as path
from os.path import join as pjoin

# print(cv.getBuildInformation())

fpath = r'C:\Users\hzx\Desktop\v_WalkingWithDog_g06_c01.avi'
# fpath = r'C:\Users\hzx\Desktop\v_WalkingWithDog_g01_c01.avi'
dstDir = r'D:\Nvidia\v_WalkingWithDog_g06_c01'
# dstDir = r'D:\Nvidia\v_WalkingWithDog_g01_c01'

pyr_scale = 0.5
levels = 3
winsize = 15
iterations = 3
poly_n = 5
poly_sigma = 1.2
flags = 0

def main():
  print(240*320*2/1024)
  calOpticalFlow(fpath, dstDir)

def showOpticalFlow(hsv, flow):
  mag, ang = cv.cartToPolar(flow[..., 0], flow[..., 1])
  hsv[...,0] = ang*180 / np.pi / 2
  hsv[...,2] = cv.normalize(mag,None,0,255,cv.NORM_MINMAX)
  rgb = cv.cvtColor(hsv, cv.COLOR_HSV2BGR)
  cv.imshow("frame2", rgb)
  return

def calOpticalFlow(srcFile, dstDir):
  if not path.exists(dstDir):
    os.mkdir(dstDir)

  cap = cv.VideoCapture()
  cap.open(srcFile)
  frame_count = cap.get(cv.CAP_PROP_FRAME_COUNT)
  # fps = cap.get(cv.CAP_PROP_FPS)
  ret, frame0 = cap.read()
  prevImg = cv.cvtColor(frame0, cv.COLOR_BGR2GRAY)

  hsv = np.zeros_like(frame0)
  hsv[...,1] = 255

  i = 0
  while (cap.isOpened()):
    ret, nextImg = cap.read()
    if not ret:
      break
    nextImg = cv.cvtColor(nextImg, cv.COLOR_BGR2GRAY)

    flow = cv.calcOpticalFlowFarneback(prevImg, nextImg, None, pyr_scale,
        levels, winsize, iterations, poly_n, poly_sigma, flags)
    # print(flow.shape)
    # print(flow.dtype)
    # print(flow[10, 10, 0])
    # print(flow[10, 10, 1])
    # break

    if True:
      showOpticalFlow(hsv, flow)
      k = cv.waitKey(30) & 0xff
      if k == 27:
        break
    else:
      dstFile = pjoin(dstDir, '%d.npy' %(i))
      np.save(dstFile, flow)
      i += 1
      # b = np.load(dstFile)
    # elif k == ord('s'):
      # print()
      # cv.imwrite('opticalfb.png',frame2)
      # cv.imwrite('opticalhsv.png',rgb)
    
    prevImg = nextImg
  cap.release
  cv.destroyAllWindows()
  return

if __name__ == '__main__':
  main()