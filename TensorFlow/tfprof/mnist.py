
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys

from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf

FLAGS = None


def main(_):
  # Create the model
  x = tf.placeholder(tf.float32, [1, 784])
  W = tf.Variable(tf.zeros([784, 10]))
  b = tf.Variable(tf.zeros([10]))
  y = tf.matmul(x, W) + b

  # merged_summary_op = tf.summary.merge_all()
  # summary_writer = tf.summary.FileWriter('/tmp/mnist_logs', tf.get_default_graph())
  #
  # with tf.Session() as sess:
  #   sess.run(tf.global_variables_initializer())
    # summary_str = sess.run(merged_summary_op)
  # summary_writer.add_summary(summary_str, 0)

  tf.profiler.profile(
    tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--data_dir', type=str, default='/tmp/tensorflow/mnist/input_data',
                      help='Directory for storing input data')
  FLAGS, unparsed = parser.parse_known_args()
  tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
