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
import tensorflow.contrib as tc

def main():
  # Create the model
  x = tf.placeholder(tf.float32, [None, 784])

  # Define loss and optimizer
  # y_ = tf.placeholder(tf.int64, [None])
  y_ = tf.placeholder(tf.float32, [None, 10])

  # y_conv, keep_prob = lenet(x)

  # Create the model
  model = MobileNetV2_mnist()
  return


class lenet():
  def __init__(self, data_format="NCHW", batch_size=0, input_size = 28):
    self.data_format = data_format
    # self.data_format = "NHWC"
    self.input_size = input_size
    # self.normalizer = tc.layers.batch_norm
    with tf.variable_scope("mnist"):
      self.is_training = tf.placeholder(tf.bool)
      self.keep_prob = tf.placeholder(tf.float32)
      if batch_size != 0 :
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[batch_size, 784])
      else :
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[None, 784])
      self.output = self._build_model(self.x)

  def _build_model(self, x):
    # self.i = 0
    init = tc.layers.xavier_initializer(dtype=tf.float32)
    data_format = "channels_first" if self.data_format == "NCHW" \
      else "channels_last"
    with tf.name_scope('reshape'):
      if self.data_format == "NCHW":
        x_image = tf.reshape(x, [-1, 1, 28, 28])
      else:
        x_image = tf.reshape(x, [-1, 28, 28, 1])
    with tf.name_scope("conv1_relu") :
      knl_size = 5
      n_out = 32
      out = tf.layers.conv2d(x_image, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=tf.nn.relu, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    # Pooling layer - downsamples by 2X.
    with tf.name_scope("pool1") :
      out = tf.layers.max_pooling2d(out, pool_size=2, strides=2,
                                    padding="same",
                                    data_format=data_format)
    # Second convolutional layer -- maps 32 feature maps to 64.
    with tf.name_scope("conv2_relu") :
      knl_size = 5
      n_out = 32
      out = tf.layers.conv2d(out, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=tf.nn.relu, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    # Second pooling layer.
    with tf.name_scope("pool2") :
      out = tf.layers.max_pooling2d(out, pool_size=2, strides=2,
                                    padding="same",
                                    data_format=data_format)
    with tf.name_scope('fc1') :
      print(out.shape)
      n_in = n_out
      n_out = 1024
      size_per_batch = out.shape[1] * out.shape[2] * out.shape[3]

      flat_out = tf.reshape(out, [-1, size_per_batch])
      out = tf.layers.dense(flat_out, n_out, activation=tf.nn.relu,
                            use_bias=False, kernel_initializer=init)
    # Dropout - controls the complexity of the model, prevents co-adaptation of
    # features.
    with tf.name_scope("dropout") :
      out = tf.layers.dropout(out, rate=self.keep_prob,
                              training=self.is_training)
    # Map the 1024 features to 10 classes, one for each digit
    with tf.name_scope('fc2') :
      n_out = 10
      out = tf.layers.dense(out, n_out, activation=None,
                            use_bias=False, kernel_initializer=init)
    return out

class MobileNetV2_mnist():
  def __init__(self, data_format="NCHW", batch_size=0, input_size = 28):
    self.data_format = data_format
    # self.data_format = "NHWC"
    self.input_size = input_size
    # self.normalizer = tc.layers.batch_norm
    with tf.variable_scope("mnist"):
      self.is_training = tf.placeholder(tf.bool)
      if batch_size != 0 :
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[batch_size, 784])
      else :
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[None, 784])
      self.output = self._build_model(self.x)


  def _build_model(self, x):
    self.i = 0
    data_format = "channels_first" if self.data_format == "NCHW" \
      else "channels_last"

    with tf.name_scope('reshape'):
      if self.data_format == "NCHW":
        x_image = tf.reshape(x, [-1, 1, 28, 28])
      else :
        x_image = tf.reshape(x, [-1, 28, 28, 1])

    with tf.variable_scope("init_conv") :
      n_out = 32
      output = tf.layers.conv2d(x_image, n_out, kernel_size=1, strides=1,
                                padding="same", data_format=data_format,
                                activation=None)
    #   output = self._BN(output)
      output = tf.nn.relu6(output)

    output = x_image
    with tf.variable_scope("body") :
      # print(output.shape)
      # output = self._inverted_bottleneck(output, 32, 32, subsample=False)
      output = self._inverted_bottleneck(output, 4, 32, subsample=False)
      # output = self._inverted_bottleneck(output, 2, 10, subsample=True)
      output = self._inverted_bottleneck(output, 4, 10, subsample=False)
      pool_size = output.shape[2:4] if self.data_format=="NCHW" \
        else output.shape[1:3]
    with tf.variable_scope("end") :
      output = tf.layers.average_pooling2d(output, pool_size, strides=1,
                                           data_format=data_format)
      # print(output.shape)
      output = tf.reshape(output, [-1, 10])
      return output

  def _BN(self, input):
    axis = 1 if self.data_format=="NCHW" else -1
    out = tf.layers.batch_normalization(input, axis=axis, scale=False,
                                        training=self.is_training,
                                        fused=True)
    # output = tf.contrib.layers.batch_norm(input, activation_fn=tf.nn.relu6,
    #                                        is_training=self.is_training,
    #                                        data_format=self.data_format)
    return out

  def _inverted_bottleneck(self, x, rate_channels, channels, subsample):
    init = tf.contrib.layers.xavier_initializer(dtype=tf.float32)
    stride = 2 if subsample else 1

    in_shape = x.shape
    if self.data_format == "NCHW":
      x_channels = in_shape[1]
      strides_4d = [1, 1, stride, stride]
    else :
      x_channels = in_shape[-1]
      strides_4d = [1, stride, stride, 1]

    n_in = int(x_channels)
    # print(type(n_in))
    # print(n_in)
    # 3x3 dw
    channel_multiplier = 1

    with tf.variable_scope("inverted_bottleneck_{}_{}_{}".format(
      self.i, rate_channels, subsample ) ) :
      if x_channels == channels:
        if stride == 2:
          w3x3 = tf.get_variable("w3x3_br0", [3, 3, x_channels, channel_multiplier],
                                 initializer=init)
          branch_0 = tf.nn.depthwise_conv2d(x, w3x3, strides=strides_4d,
                                            padding="SAME",
                                            data_format=self.data_format)
          # branch_0 = self._BN(branch_0)
        else :
          branch_0 = x

      # 1x1 pointwise
      n_out = rate_channels * n_in
      data_format = "channels_first" if self.data_format=="NCHW" \
        else "channels_last"
      branch_1 = tf.layers.conv2d(x, n_out, kernel_size=1, strides=1,
                       padding="same", data_format=data_format,
                       activation=None, use_bias=False,
                       kernel_initializer=init)
      # branch_1 = self._BN(branch_1)
      branch_1 = tf.nn.relu6(branch_1)
      # w1x1 = tf.get_variable("w1x1", [1, 1, n_in, n_out], initializer=init)
      # b1x1 = tf.get_variable("b1x1", [n_out], initializer=init)
      # branch_1 = tf.nn.conv2d(x, w1x1, strides=[1, 1, stride, stride],
      #                       padding="SAME", data_format=self.data_format)
      # 3x3 depthwise
      n_in = n_out
      # print(n_in)

      # print(n_out)
      w3x3 = tf.get_variable("w3x3_br1", [3, 3, n_in, channel_multiplier],
                             initializer=init)
      # b3x3 = b1x1 = tf.get_variable("b3x3", [n_out], initializer=init)
      branch_1 = tf.nn.depthwise_conv2d(branch_1, w3x3, strides=strides_4d,
                                      padding="SAME", data_format=self.data_format)
      # branch_1 = self._BN(branch_1)
      branch_1 = tf.nn.relu6(branch_1)
      # 1x1
      n_out = channels
      branch_1 = tf.layers.conv2d(branch_1, n_out, kernel_size=1, strides=1,
                                padding="same", data_format=data_format,
                                activation=None, use_bias=False,
                                kernel_initializer=init)
      # branch_1 = self._BN(branch_1)
      # print(self.i)
      if x_channels == channels:
        output = tf.add(branch_0, branch_1)
      else :
        output = branch_1
    self.i += 1
    return output
# end class MobileNetV2_mnist

class fcn_lenet():
  def __init__(self, data_format="NCHW", batch_size=0, input_size=28):
    self.data_format = data_format
    # self.data_format = "NHWC"
    self.input_size = input_size
    # self.normalizer = tc.layers.batch_norm
    with tf.variable_scope("mnist"):
      if batch_size != 0:
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[batch_size, 784])
      else:
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[None, 784])
      self.output = self._build_model(self.x)
    return

  def _build_model(self, x):
    init = tc.layers.xavier_initializer(dtype=tf.float32)
    data_format = "channels_first" if self.data_format == "NCHW" \
      else "channels_last"
    with tf.name_scope('reshape'):
      if self.data_format == "NCHW":
        x_image = tf.reshape(x, [-1, 1, 28, 28])
      else:
        x_image = tf.reshape(x, [-1, 28, 28, 1])
    with tf.name_scope("conv1_relu") :
      knl_size = 5
      n_out = 32
      out = tf.layers.conv2d(x_image, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=tf.nn.relu, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    # Pooling layer - downsamples by 2X.
    with tf.name_scope("pool1") :
      out = tf.layers.max_pooling2d(out, pool_size=2, strides=2,
                                    padding="same",
                                    data_format=data_format)
    # Second convolutional layer -- maps 32 feature maps to 64.
    with tf.name_scope("conv2_relu") :
      knl_size = 5
      n_out = 32
      out = tf.layers.conv2d(out, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=tf.nn.relu, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    # Second pooling layer.
    with tf.name_scope("pool2") :
      out = tf.layers.max_pooling2d(out, pool_size=2, strides=2,
                                    padding="same",
                                    data_format=data_format)
    with tf.name_scope("pointwise") :
      knl_size = 1
      n_out = 10
      out = tf.layers.conv2d(out, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=None, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    pool_size = out.shape[2:4] if self.data_format == "NCHW" \
      else out.shape[1:3]
    with tf.name_scope("global_avg_pool") :
      out = tf.layers.average_pooling2d(out, pool_size, strides=1,
                                        data_format=data_format)
    out = tf.reshape(out, [-1, 10])
    return out

if __name__ == '__main__':
  main()

# reference
# https://github.com/timctho/mobilenet-v2-tensorflow/blob/master/models.py
# https://github.com/tonylins/pytorch-mobilenet-v2/blob/master/MobileNetV2.py

# BN
# http://blog.csdn.net/FontThrone/article/details/76652772
# http://www.liulizhe.com/2017/09/12/cnn%E4%B8%AD%E7%9A%84batch-normalization%E5%8F%8A%E5%85%B6tensorflow%E7%94%A8%E6%B3%95/