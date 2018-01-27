# Copyright 2015 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================

"""A deep MNIST classifier using convolutional layers.

See extensive documentation at
https://www.tensorflow.org/get_started/mnist/pros
"""
# Disable linter warnings to maintain consistency with tutorial.
# pylint: disable=invalid-name
# pylint: disable=g-bad-import-order

# import sys
# import tempfile
# import os.path as path
# import time

import tensorflow as tf

def main():
  # Create the model
  x = tf.placeholder(tf.float32, [None, 784])

  # Define loss and optimizer
  # y_ = tf.placeholder(tf.int64, [None])
  y_ = tf.placeholder(tf.float32, [None, 10])

  # y_conv, keep_prob = lenet(x)


  return


def lenet(x):
  """deepnn builds the graph for a deep net for classifying digits.

  Args:
    x: an input tensor with the dimensions (N_examples, 784), where 784 is the
    number of pixels in a standard MNIST image.

  Returns:
    A tuple (y, keep_prob). y is a tensor of shape (N_examples, 10), with values
    equal to the logits of classifying the digit into one of 10 classes (the
    digits 0-9). keep_prob is a scalar placeholder for the probability of
    dropout.
  """
  # Reshape to use within a convolutional neural net.
  # Last dimension is for "features" - there is only one here, since images are
  # grayscale -- it would be 3 for an RGB image, 4 for RGBA, etc.
  with tf.name_scope('reshape'):
    x_image = tf.reshape(x, [-1, 1, 28, 28])
    # print(x_image.shape)

  # First convolutional layer - maps one grayscale image to 32 feature maps.
  n_in = 1
  n_out = 32
  with tf.name_scope('conv1'):
    W_conv1 = weight_variable([5, 5, n_in, n_out])
    b_conv1 = bias_variable([n_out])
    conv_res = conv2d(x_image, W_conv1)
    conv_res = tf.nn.bias_add(conv_res, b_conv1, data_format="NCHW")
    h_conv1 = tf.nn.relu(conv_res)

  # Pooling layer - downsamples by 2X.
  with tf.name_scope('pool1'):
    h_pool1 = max_pool_2x2(h_conv1)

  # Second convolutional layer -- maps 32 feature maps to 64.
  n_in = n_out
  n_out = 64
  with tf.name_scope('conv2'):
    W_conv2 = weight_variable([5, 5, n_in, n_out])
    b_conv2 = bias_variable([n_out])
    conv_res = conv2d(h_pool1, W_conv2)
    conv_res = tf.nn.bias_add(conv_res, b_conv2, data_format="NCHW")
    h_conv2 = tf.nn.relu(conv_res)

  # Second pooling layer.
  with tf.name_scope('pool2'):
    h_pool2 = max_pool_2x2(h_conv2)

  # Fully connected layer 1 -- after 2 round of downsampling, our 28x28 image
  # is down to 7x7x64 feature maps -- maps this to 1024 features.
  n_in = n_out
  n_out = 1024
  with tf.name_scope('fc1'):
    h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * n_in])
    W_fc1 = weight_variable([n_in * 7 * 7, n_out])
    # b_fc1 = bias_variable([n_out])
    # print(W_fc1.shape)
    # wfc1_shape = W_fc1.shape
    h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1))

  # Dropout - controls the complexity of the model, prevents co-adaptation of
  # features.
  with tf.name_scope('dropout'):
    keep_prob = tf.placeholder(tf.float32)
    h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

  # Map the 1024 features to 10 classes, one for each digit
  n_in = n_out
  n_out = 10
  with tf.name_scope('fc2'):
    W_fc2 = weight_variable([n_in, n_out])
    # b_fc2 = bias_variable([n_out])
    y_conv = tf.matmul(h_fc1_drop, W_fc2)
  return y_conv, keep_prob

def conv2d(x, W):
  """conv2d returns a 2d convolution layer with full stride."""
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME',
                      data_format="NCHW")

def max_pool_2x2(x):
  """max_pool_2x2 downsamples a feature map by 2X."""
  return tf.nn.max_pool(x, ksize=[1, 1, 2, 2],
                        strides=[1, 1, 2, 2], padding='SAME',
                        data_format="NCHW")

def weight_variable(shape):
  """weight_variable generates a weight variable of a given shape."""
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  """bias_variable generates a bias variable of a given shape."""
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)

class MobileNetV2_mnist():
  def __init__(self, is_training=True, data_format="NCHW", input_size = 28):
    self.is_training = is_training
    self.data_format = data_format
    # self.data_format = "NHWC"
    self.input_size = input_size
    # self.normalizer = tc.layers.batch_norm
    self.bn_params = {'is_training': self.is_training}
    with tf.variable_scope("mnist"):
      if data_format == "NCHW":
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[None, 1, input_size, input_size])
      else :
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[None, input_size, input_size, 1])

      self.output = self._build_model(self.x)


  def _build_model(self, x):
    self.i = 0
    with tf.variable_scope("init_conv") :
      # w = tf.get_variable("first_w", )
      n_out = 16
      data_format = "channels_first" if self.data_format == "NCHW" \
        else "channels_last"
      output = tf.layers.conv2d(x, n_out, kernel_size=3, strides=1,
                                padding="same", data_format=data_format,
                                activation=None)
      print(output.shape)
      output2 = tf.contrib.layers.batch_norm(x, activation_fn=None,
                                            is_training=self.is_training,
                                            data_format=self.data_format)
      # output2 = tf.contrib.layers.batch_norm(x, activation_fn=tf.nn.relu6,
      #                                        is_training=self.is_training,
      #                                        data_format=self.data_format)
      print(output2.shape)
      return
      output = self._inverted_bottleneck(output, 4, 32, subsample=False)
      output = self._inverted_bottleneck(output, 4, 32, subsample=False)
      output = self._inverted_bottleneck(output, 1, 10, subsample=True)
      pool_size = output.shape[2:4] if self.data_format=="NCHW" \
        else output.shape[1:3]
      data_format = "channels_first" if self.data_format == "NCHW" \
        else "channels_last "
      output = tf.layers.average_pooling2d(output, pool_size, strides=None,
                                           data_format=data_format)
      print(output.shape)
      return output


  def _inverted_bottleneck(self, x, rate_channels, channels, subsample):
    init = tf.contrib.layers.xavier_initializer(dtype=tf.float32)
    in_shape = x.shape
    n_in = in_shape[1]
    print(type(n_in))
    n_in = in_shape[1] if self.data_format=="NCHW" else in_shape[-1]
    n_in = int(n_in)
    # print(type(n_in))
    # print(n_in)
    stride = 2 if subsample else 1
    with tf.name_scope("inverted_bottleneck_{}_{}_{}".format(
      self.i, rate_channels, subsample ) ) :
      # 1x1 pointwise
      n_out = rate_channels * n_in
      data_format = "channels_first" if self.data_format=="NCHW" \
        else "channels_last "
      output = tf.layers.conv2d(x, n_out, kernel_size=1, strides=stride,
                       padding="same", data_format=data_format,
                       activation=None, use_bias=False,
                       kernel_initializer=init)
      output = tf.contrib.layers.batch_norm(x, activation_fn=tf.nn.relu6,
                                            is_training=self.is_training,
                                            data_format=self.data_format)
      # output = tf.layers.batch_normalization(x, )
      # w1x1 = tf.get_variable("w1x1", [1, 1, n_in, n_out], initializer=init)
      # b1x1 = tf.get_variable("b1x1", [n_out], initializer=init)
      # output = tf.nn.conv2d(x, w1x1, strides=[1, 1, stride, stride],
      #                       padding="SAME", data_format=self.data_format)
      # 3x3 depthwise
      n_in = n_out
      print(n_in)
      print(n_out)
      w3x3 = tf.get_variable("w3x3", [3, 3, n_in, n_out], initializer=init)
      # b3x3 = b1x1 = tf.get_variable("b3x3", [n_out], initializer=init)
      # output = tf.nn.depthwise_conv2d(x, w3x3, strides=[1, 1, stride, stride],
      #                                 padding="SAME", data_format=self.data_format)
      output = tf.nn.depthwise_conv2d(x, w3x3, strides=[1, 1, 1, 1],
                                      padding="SAME", data_format=self.data_format)
      output = tf.contrib.layers.batch_norm(x, activation_fn=tf.nn.relu6,
                                            is_training=self.is_training,
                                            data_format=self.data_format)
      # 1x1
      n_out = channels
      output = tf.layers.conv2d(x, n_out, kernel_size=1, strides=stride,
                                padding="same", data_format=data_format,
                                activation=None, use_bias=False,
                                kernel_initializer=init)
      # w1x1_1 = tf.get_variable("w1x1_1", [1, 1, n_in, n_out], initializer=init)
      # b1x1_1 = tf.get_variable("b1x1_1", [n_out], initializer=init)
      # output = tf.nn.conv2d(x, w1x1_1, strides=[1, 1, stride, stride],
      #                       padding="SAME", data_format=self.data_format)
      output = tf.contrib.layers.batch_norm(x, activation_fn=None,
                                            is_training=self.is_training,
                                            data_format=self.data_format)
      output = tf.add(x, output)
    self.i += 1
    return output

# end class MobileNetV2_mnist


if __name__ == '__main__':
  main()

# reference
# https://github.com/timctho/mobilenet-v2-tensorflow/blob/master/models.py
# https://github.com/tonylins/pytorch-mobilenet-v2/blob/master/MobileNetV2.py

# BN
# http://blog.csdn.net/FontThrone/article/details/76652772
# http://www.liulizhe.com/2017/09/12/cnn%E4%B8%AD%E7%9A%84batch-normalization%E5%8F%8A%E5%85%B6tensorflow%E7%94%A8%E6%B3%95/