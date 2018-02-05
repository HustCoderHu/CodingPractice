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
import json
# import numpy as np
import numpy as np
import json

from tensorflow.examples.tutorials.mnist import input_data
import tensorflow as tf
from tensorflow import layers

cwd = os.getcwd()
sys.path.append(cwd)
import mnist_model

FLAGS = None
mnist_dir = r"E:\github_repo\tftest\mnist"
model_dir = path.join(mnist_dir, "model")
SavedModel_dir= path.join(mnist_dir, "SavedModel")
data_dir = path.join(mnist_dir, "MNIST_data")

batch_size = 50
max_iter = int(55000 / batch_size * 1)
test_interval = 20
snapshot_intval = 500
display = 10
keep_prob = 0.5

def main():
  # test_mobileV2_mnist()
  # test_mobileV2_mnist(profile=True)
  # default_lenet()
  test_fcn_lenet()

  return

def test_fcn_lenet() :
  # Create the model
  data_format = "NHWC"
  model = mnist_model.fcn_lenet(data_format)
  # Define loss and optimizer
  y_ = tf.placeholder(tf.float32, [None, 10])
  # Build the graph for the deep net

  with tf.name_scope('accuracy'):
    correct_prediction = tf.equal(tf.argmax(model.output, 1), tf.argmax(y_, 1))
    correct_prediction = tf.cast(correct_prediction, tf.float32)
    acc = tf.reduce_mean(correct_prediction, name="acc")
  tf.summary.scalar('accuracy', acc)

  with tf.name_scope('loss'):
    # cross_entropy = tf.losses.sparse_softmax_cross_entropy(
    # labels=y_, logits=y_conv)
    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=model.output)
    # cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=y_, logits=y_conv)
    cross_entropy = tf.reduce_mean(cross_entropy)
  tf.summary.scalar('cross_entropy', cross_entropy)

  with tf.name_scope('adam_optimizer'):
    optimizer = tf.train.AdamOptimizer(1e-2)
    train_op = optimizer.minimize(cross_entropy)
  tf.summary.scalar('lr', optimizer._lr_t)

  # print(cross_entropy.name) # loss/Mean:0
  # print(accuracy.name) # accuracy/acc:0
  # graph_location = tempfile.mkdtemp()
  # graph_location = r"D:\github_repo\tftest\mnist_deep_log"
  # print('Saving graph to: %s' % graph_location)
  # train_writer = tf.summary.FileWriter(graph_location)
  # train_writer.add_graph(tf.get_default_graph())
  LOG_DIR = path.join(mnist_dir, "log-fcn_lenet")
  train_dir = path.join(LOG_DIR, "train")
  train_writer = tf.summary.FileWriter(train_dir)
  train_writer.add_graph(tf.get_default_graph())
  test_dir = path.join(LOG_DIR, "test")
  test_writer = tf.summary.FileWriter(test_dir)

  # Add ops to save and restore all the variables.
  saver = tf.train.Saver()

  # Import data
  mnist = input_data.read_data_sets(data_dir, one_hot=True,
                                    source_url=
                                    'http://yann.lecun.com/exdb/mnist/')

  merged = tf.summary.merge_all()
  config = tf.ConfigProto()
  # config.gpu_options.allow_growth = True
  config.gpu_options.per_process_gpu_memory_fraction = 0.75
  hooks = []

  tf.train.MonitoredTrainingSession(save_checkpoint_secs=None, config=config)

  with tf.Session(config=config) as sess:
    tf.global_variables_initializer().run()
    for i in range(max_iter):
      batch = mnist.train.next_batch(batch_size)
      summary, _, loss = sess.run([merged, train_op, cross_entropy],
          feed_dict={model.x: batch[0], y_: batch[1] })
      train_writer.add_summary(summary, i)
      if i % display == 0 and i != 0:
        print("iter {}: ".format(i))
        print("  loss: %g" % loss)
      # test
      if i % test_interval == 0:
        batch = mnist.test.next_batch(batch_size)
        summary, test_acc = sess.run([merged, acc], feed_dict={
            model.x: batch[0], y_: batch[1]})
        test_writer.add_summary(summary, i)
        print('--  test accuracy: %g' % test_acc)
      if i % snapshot_intval == 0 and i != 0:
        _prefix = "iter-{}".format(i)
        ckpt_path = path.join(model_dir, _prefix)
        save_path = saver.save(sess, ckpt_path)
        print("=== snapshot to {}".format(save_path))
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
  return

  print("----------------------------")
  print("save_path: {}".format(save_path))
  print("begin test")
  # test
  # config.gpu_options.allow_growth = True
  # tf.reset_default_graph()
  print("----------------------------")
  with tf.Session(config=config) as sess:
    _prefix = "iter-{}".format(max_iter - 1)
    saver.restore(sess, save_path)

    # with tf.variable_scope('accuracy', reuse=True) :
    #   acc = tf.get_variable(name="acc")
    # whole_acc = acc.eval(feed_dict={model.x: mnist.test.images,
                                    # y_: mnist.test.labels})
    whole_acc = 0  
    print('whole val set accuracy %g' % whole_acc)
  return

if __name__ == '__main__':
  main()
  # parser = argparse.ArgumentParser()
  # parser.add_argument('--data_dir', type=str,
  #                     default='/tmp/tensorflow/mnist/input_data',
  #                     help='Directory for storing input data')
  # FLAGS, unparsed = parser.parse_known_args()
  # tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
