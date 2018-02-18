import os.path as path
import tensorflow as tf
import numpy as np
import cv2 as cv

# from tensorflow.examples.tutorials.mnist import input_data
from tensorflow.contrib.learn.python.learn.datasets import mnist

def test-DatasetAPI():
  num_epochs = 5
  buffer_size = 11 * 5 + 1 # 大于样本数
  batch_size = 11

  filenames = ["test.tfrecords"]
  dataset = tf.data.TFRecordDataset(filenames)
  dset = dataset.repeat(num_epochs)
  dset = dset.shuffle(buffer_size)
  dset = dset.batch(batch_size)
  _iter = dset.make_one_shot_iterator()
  next_one = _iter.get_next()

def _parse_function(example_proto):
  features = {"image": tf.FixedLenFeature((), tf.string, default_value=""),
              "label": tf.FixedLenFeature((), tf.int32, default_value=0)}
  parsed_features = tf.parse_single_example(example_proto, features)
  return parsed_features["image"], parsed_features["label"]

def test-tfrecord():
  mnist_dir = r"D:\github_repo\tftest\mnist"
  # mnist_dir = r"E:\github_repo\tftest\mnist"
  model_dir = path.join(mnist_dir, "model")
  SavedModel_dir= path.join(mnist_dir, "SavedModel")
  data_dir = path.join(mnist_dir, "MNIST_data")
  
  img = cv.imread("1_01.jpg")
  
  data_sets = mnist.read_data_sets(data_dir,
      dtype=tf.uint8, one_hot=True, source_url=
          'http://yann.lecun.com/exdb/mnist/')
  
  train_set = data_sets.train
  
  images = train_set.images
  labels = train_set.labels
  print(type(images))
  print(type(labels))
  print(images.shape)
  print(labels.shape)
  print(type(images[0]))
  print(images[0].shape)
  
  image_dir = r"F:\Lab408\jinzhengu\a_root"
  img_list = ["1_01.jpg", "5_01.jpg", "7_01.jpg", "13_01.jpg", "14_01.jpg"]
  img_list2 = ["62.bmp", "63.bmp", "64.bmp", "65.bmp", "66.bmp", "67.bmp"]
  img_list.extend(img_list2)
  label_list = [1, 5, 7, 13, 14]
  label_list = [1, 5, 7, 13, 14, 62, 63, 64, 65, 66, 67]
  img_num = len(img_list)
  
  # for img_name in img_list:
  #   img_path = path.join(image_dir, img_name)
  #   img = cv.imread(img_path)
  #   print(img.shape)
  #   img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
  #   cv.imshow("aa", img)
  #   cv.waitKey()
  
  # exit(0)
  
  # img_raw = tf.image.decode_jpeg(img_path)
  
  int64_lda = lambda val : tf.train.Feature(
      int64_list=tf.train.Int64List(value=[val]) )
  byte_lda = lambda val : tf.train.Feature(
      bytes_list=tf.train.BytesList(value=[val]) )
  
  # compression_type = tf.python_io.TFRecordCompressionType.NONE
  # compression_type = tf.python_io.TFRecordCompressionType.ZLIB
  compression_type = tf.python_io.TFRecordCompressionType.GZIP
  options_ = tf.python_io.TFRecordOptions(compression_type)
  with tf.python_io.TFRecordWriter("test.tfrecords", options_) as writer:
    for idx, img_name in enumerate(img_list):
      img_path = path.join(image_dir, img_name)
      data = cv.imread(img_path) # ndarray
      data = cv.cvtColor(data, cv.COLOR_BGR2RGB)
      print(img_name)
      print(type(data.tobytes()))
      
      feature_map = {
          "image": byte_lda(data.tobytes()), # tobytes() type: <class 'bytes'>
          "label": int64_lda(label_list[idx])
        }
      features_ = tf.train.Features(feature = feature_map)
      example = tf.train.Example(features = features_)
      writer.write(example.SerializeToString())