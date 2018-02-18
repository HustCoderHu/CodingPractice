import os
import os.path as path
import tensorflow as tf
import tensorflow.contrib as tc
import numpy as np
import cv2 as cv

import time

pr_type = lambda var : print(type(var))
pr_shape = lambda var : print(var.shape)

def main():
  test_dataset()

def test_dataset():
  # out = tf.constant(value=1.0, shape=[4, 7, 7, 3])
  # out = tf.reduce_mean(out, axis=(1, 2))
  # print(out.shape) # (4, 3)
  # return 

  img_dir = r"F:\Lab408\jinzhengu\test-it"
  img_dir = r"F:\Lab408\jinzhengu\atest\a"
  
  num_epochs = 5
  # buffer_size = 9 * 5 + 1 # 大于样本数
  batch_sz = 20

  img_list = os.listdir(img_dir)
  img_list = [path.join(img_dir, _name) for _name in img_list]
  # print(len(img_list))
  # return
  # for img_name in img_list:
  #   _path = path.join(img_dir, img_name)
  #   img = cv.imread(_path)
  #   print(img.shape)
  # return
  
  
  imglist_t = tf.constant(img_list)
  lblist_t = tf.constant(value=0.0, shape=[len(img_list)])
  # print(img_list)
  # print(imglist_t.shape)
  # print(lblist_t.shape)

  dataset = tf.data.Dataset().from_tensor_slices((imglist_t, lblist_t))
  # print(dataset.output_shapes)
  # print()
  # return
  
  dset = dataset.map(_mapfunc, num_parallel_calls=8)
  buffer_size = len(img_list) + 1
  buffer_size = 30
  # dset = dset.shuffle(buffer_size, reshuffle_each_iteration=False)
  dset = dset.repeat() # num_epochs
  dset = dset.batch(batch_sz) # item shape () -> (batch, )
  # dset = dset.map(_parse_function, num_parallel_calls=4)
  prefetch_sz = 3
  dset = dset.prefetch(prefetch_sz)
  
  _iter = dset.make_one_shot_iterator()
  next_one = _iter.get_next()
  pr_type(next_one)
  print(len(next_one))
  # print(type(next_one))
  t_batchimg, t_batchlabel, t_batchfile = next_one
  pr_type(t_batchimg)
  pr_shape(t_batchimg)
  # return
  
  # t_out = t_batchimg
  t_out = tf.reshape(next_one[0], [-1, 200, 250, 3])
  # t_out = tf.reshape(t_batchimg, [-1, 200, 250, 3])
  # t_out = tf.reshape(t_batchimg, [-1, 28, 28, 3])
  init = tc.layers.xavier_initializer(dtype=tf.float32)
  data_format = "channels_last"

  n_out = 32
  t_out = tf.layers.conv2d(t_out, n_out, kernel_size=3, strides=1,
      padding="same", data_format=data_format, activation=None,
      use_bias=False, kernel_initializer=init)
  # t_out = tf.nn.relu6(t_out)

  # n_out = 64
  # t_out = tf.layers.conv2d(t_out, n_out, kernel_size=3, strides=1,
  #     padding="same", data_format=data_format, activation=None,
  #     use_bias=False, kernel_initializer=init)
  # t_out = tf.nn.relu6(t_out)
  
  # size_per_batch = t_out.shape[1] * t_out.shape[2] * t_out.shape[3]
  # flat_out = tf.reshape(t_out, [-1, size_per_batch])
  # n_out = 10
  # t_out = tf.layers.dense(flat_out, n_out, activation=tf.nn.relu6,
  #                           use_bias=False, kernel_initializer=init)

  # t_out = tf.layers.conv2d(t_out, n_out, kernel_size=1, strides=1,
  #     padding="same", data_format=data_format, activation=None,
  #     use_bias=False, kernel_initializer=init)
  
  
  # t_out = tf.nn.relu(t_out)
  # t_out = tf.reduce_mean(t_out, axis=(1, 2))
  # print(type(gap))
  # return
  # print(gap.shape)
  # return


  # print("next_one type: {}".format(type(next_one)))
  # print("next_one shape: {}".format(next_one.shape))
  # return
  # init = tf.variables_initializer([tf.global_variables])
  # op_group = tf.group(tf.global_variables(), tf.local_variables())
  op_init1 = tf.variables_initializer(tf.global_variables())
  op_init2 = tf.variables_initializer(tf.local_variables())
  op_group = tf.group(op_init1, op_init2)
  # init = tf.variables_initializer([tf.global_variables(), tf.local_variables()])
  config = tf.ConfigProto()
  config.gpu_options.allow_growth = True
  with tf.Session(config = config) as sess:
    sess.run(op_group)
    
    n_count = 2 * prefetch_sz

    for i in range(n_count):
      _out = sess.run(t_out)
    print("warm up finish")
    
    n_count = 2 * prefetch_sz

    # start = time.perf_counter()
    # for i in range(n_count):
    #   _out = sess.run(t_batchimg)
    # elapsed = time.perf_counter() - start
    # print('pure IO Elapsed %.6f seconds.' % elapsed)

    start = time.perf_counter()
    for i in range(n_count):
      _out = sess.run(t_out)
    elapsed = time.perf_counter() - start
    print('IO + gpu Elapsed %.6f seconds.' % elapsed)

    # _out = sess.run(t_out)
    # pr_type(_out)
    # pr_shape(_out)
    # _out = sess.run(next_one)
    # pr_type(_out)
    # print(len(_out))
    # pr_type(_out[0])
    # pr_shape(_out[0])
    
    # while True:
    #   try:
    #     start = time.perf_counter()
    #     _out = sess.run(t_out)
    #     _out = sess.run(t_out)
    #     elapsed = time.perf_counter() - start
    #     print('Elapsed %.6f seconds.' % elapsed)
    #   except tf.errors.OutOfRangeError:
    #     break
    # print(gap.shape)
  #   img, label, fname = sess.run(next_one)
  #   example = sess.run(next_one)
  #   print(fname)
  #   print(type(img))
  #   print(img.shape)
  #   print(img.dtype)
  #   _batch_size = img.shape[0]
  #   for i in range(_batch_size):
  #     _img = cv.cvtColor(img[i].astype(np.uint8), cv.COLOR_RGB2BGR)
  #     # print(img[i].shape)
  #     cv.imshow("%d" % i, _img)
  
  # cv.waitKey()
    # tf.global_variables_initializer().run()



def _mapfunc(filename, label):
  # image_string = tf.read_file(filename)
  # image_decoded = tf.image.decode_bmp(image_string)
  # image_decoded = tf.image.decode_image(image_string) # ValueError: 'images' contains no shape
  # print(image_decoded.shape)
  # image_resized = tf.image.resize_images(image_decoded, [500, 500])
  # return image_resized, label, filename
  # batch_size = filename.shape[0]
  
  # decoded_list = []
  # i = 0
  # while i < batch_size:
  #   _file = filename[i]
  #   image_decoded = tf.image.decode_bmp(_file)
  #   image_resized = tf.image.resize_images(image_decoded, [200, 250])
  #   decoded_list.append([image_resized, label[i], _file])
  
  # cond = lambda example, idx : idx < batch_size
  # def loop_body(t_filelist, t_labellist, idx):
  #   image_decoded = tf.image.decode_bmp(t_filelist[idx])
  #   image_resized = tf.image.resize_images(image_decoded, [200, 250])
  #   return
  with tf.device('/cpu:0'):
    # <https://www.tensorflow.org/performance/performance_guide>
    # idx = tf.constant(0)
    # print(type(filename))
    # print(filename.shape)
    # _i_file = filename[0]
    # print(type(_i_file))
    # print(_i_file.shape)
    # image_resized = 0
    # print("lineline")
    img_raw = tf.read_file(filename)
    decoded = tf.image.decode_bmp(img_raw)
    # resized = tf.image.decode_image(decoded) # ValueError: 'images' contains no shape
    # print(image_decoded.shape)
    resized = tf.image.resize_images(decoded, [200, 250])
    # resized = tf.image.resize_images(decoded, [28, 28])
    # image_resized = image_decoded
  return resized, label, filename

if __name__ == "__main__":
  main()

# reference
# <https://zhuanlan.zhihu.com/p/30751039>