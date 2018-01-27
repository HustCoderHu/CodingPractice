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

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys
import tempfile
import os
import os.path as path
import time
from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf

cwd = os.getcwd()
sys.path.append(cwd)
import mnist_model

FLAGS = None
data_dir = r"D:\github_repo\tftest\MNIST_data"

def main():
  # Import data
  mnist = input_data.read_data_sets(data_dir, one_hot=True, 
                                    source_url='http://yann.lecun.com/exdb/mnist/')

  # Create the model
  model = mnist_model.MobileNetV2_mnist()
  return

  # Define loss and optimizer
  # y_ = tf.placeholder(tf.int64, [None])
  y_ = tf.placeholder(tf.float32, [None, 10])

  # Build the graph for the deep net

  with tf.name_scope('loss'):
    # cross_entropy = tf.losses.sparse_softmax_cross_entropy(
        # labels=y_, logits=y_conv)
    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=model.output)
    # cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=y_, logits=y_conv)
    cross_entropy = tf.reduce_mean(cross_entropy)

  with tf.name_scope('adam_optimizer'):
    train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)

  with tf.name_scope('accuracy'):
    correct_prediction = tf.equal(tf.argmax(model.output, 1), tf.argmax(y_, 1))
    correct_prediction = tf.cast(correct_prediction, tf.float32)
    acc = tf.reduce_mean(correct_prediction, name="acc")

  # print(cross_entropy.name) # loss/Mean:0
  # print(accuracy.name) # accuracy/acc:0
  # graph_location = tempfile.mkdtemp()
  graph_location = r"D:\github_repo\tftest\mnist_deep_log"
  print('Saving graph to: %s' % graph_location)
  train_writer = tf.summary.FileWriter(graph_location)
  train_writer.add_graph(tf.get_default_graph())

  # Add ops to save and restore all the variables.
  saver = tf.train.Saver()

  model_dir = r"D:\github_repo\tftest\mnist_deep_model"

  config = tf.ConfigProto()
  # config.gpu_options.allow_growth = True
  config.gpu_options.per_process_gpu_memory_fraction = 0.75
  # return
  batch_size = 50
  max_iter = 1 # int(55000 / batch_size * 1)
  snapshot_intval = 500

  save_path = "a"
  with tf.Session(config = config) as sess:
    sess.run(tf.global_variables_initializer())
    for i in range(max_iter):
      batch = mnist.train.next_batch(batch_size)
      if i % 100 == 0:
        train_accuracy = acc.eval(feed_dict={
            x: batch[0], y_: batch[1], keep_prob: 1.0})
        print('iter %d, training accuracy %g' % (i, train_accuracy))
      train_step.run(feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})
      if i % snapshot_intval == 0 and i > 0:
        _prefix = "iter-{}".format(i)
        ckpt_path = path.join(model_dir, _prefix)
        save_path = saver.save(sess, ckpt_path)
        print("snapshot to {}".format(save_path))
    # train finish
    _prefix = "iter-{}".format(max_iter - 1)
    ckpt_path = path.join(model_dir, _prefix)
    save_path = saver.save(sess, ckpt_path)
    print("snapshot to {}".format(save_path))
    # error on my 750ti
    # Allocator (GPU_0_bfc) ran out of memory trying to allocate 957.03MiB
    # Resource exhausted: OOM when allocating tensor with shape[10000,32,28,28]
    # print('whole val set accuracy %g' % accuracy.eval(feed_dict={
    #   x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))
  print("----------------------------")
  print("save_path: {}".format(save_path))
  print("begin test")
  # test
  # config.gpu_options.allow_growth = True
  # tf.reset_default_graph()
  print("----------------------------")
  with tf.Session(config = config) as sess:
    iter = max_iter - max_iter % snapshot_intval
    _prefix = "iter-{}".format(max_iter - 1)
    meta_path = path.join(model_dir, _prefix + ".meta")
    # new_saver = tf.train.import_meta_graph(meta_path)
    saver.restore(sess, save_path)

    # with tf.variable_scope('accuracy', reuse=True) :
    #   acc = tf.get_variable(name="acc")
    print('whole val set accuracy %g' % accuracy.eval(feed_dict={
      x: mnist.test.images, y_: mnist.test.labels, keep_prob: 1.0}))

if __name__ == '__main__':
  main()
  # parser = argparse.ArgumentParser()
  # parser.add_argument('--data_dir', type=str,
  #                     default='/tmp/tensorflow/mnist/input_data',
  #                     help='Directory for storing input data')
  # FLAGS, unparsed = parser.parse_known_args()
  # tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
