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
import numpy as np

from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf

cwd = os.getcwd()
sys.path.append(cwd)
TF_base = r"E:\github_repo\CodingPractice\TensorFlow"
sys.path.append(path.join(TF_base, "mnist"))

import mnist_model

FLAGS = None
mnist_dir = r"E:\github_repo\tftest\mnist"
model_dir = path.join(mnist_dir, "model")
data_dir = path.join(mnist_dir, "MNIST_data")

batch_size = 40
max_iter = int(55000 / batch_size * 1)
test_interval = 4
snapshot_intval = 500
display = 2
keep_prob = 0.5

def main():
	# test_mobileV2_mnist()
	# test_mobileV2_mnist(profile=True)
	default_lenet()
	return

def default_lenet():
	# Create the model
	data_format = "NHWC"
	model = mnist_model.lenet(data_format, batch_size=batch_size)
	# Define loss and optimizer
	y_ = tf.placeholder(tf.float32, [batch_size, 10])
	# Build the graph for the deep net

	with tf.name_scope('accuracy'):
		correct_prediction = tf.equal(tf.argmax(model.output, 1), tf.argmax(y_, 1))
		correct_prediction = tf.cast(correct_prediction, tf.float32)
		acc = tf.reduce_mean(correct_prediction, name="acc")

	with tf.name_scope('loss'):
		# cross_entropy = tf.losses.sparse_softmax_cross_entropy(
				# labels=y_, logits=y_conv)
		cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=model.output)
		# cross_entropy = tf.nn.softmax_cross_entropy_with_logits_v2(labels=y_, logits=y_conv)
		cross_entropy = tf.reduce_mean(cross_entropy)

	profiler = tf.profiler.Profiler(tf.get_default_graph())

	with tf.name_scope('adam_optimizer'):
		train_op = tf.train.AdamOptimizer(1e-2).minimize(cross_entropy)

	# Import data
	x = np.zeros([batch_size, 784], np.float32)
	labels = np.zeros([batch_size, 10], np.float32)

	# profiler = tf.profiler.Profiler(tf.get_default_graph())
	config = tf.ConfigProto()
	# config.gpu_options.allow_growth = True
	# config.gpu_options.per_process_gpu_memory_fraction = 0.75
	with tf.Session(config = config) as sess:
		sess.run(tf.global_variables_initializer())
		# profiler = tf.profiler.Profiler(sess.graph)
		options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
		opts = tf.profiler.ProfileOptionBuilder.time_and_memory()
		run_meta = tf.RunMetadata()
		for i in range(max_iter):
			if i % 5 == 0 :
				run_meta = tf.RunMetadata()
				sess.run(train_op, options=options, run_metadata=run_meta,
								 feed_dict={model.is_training: True,
														model.keep_prob: keep_prob,
														model.x: x, y_: labels })
				# sess.run(acc, options=options, run_metadata=run_meta,
				#          feed_dict={model.is_training: False,
				#                     model.keep_prob: 1,
				#                     model.x: x, y_: labels})

				profiler.add_step(i, run_meta)
				# Or profile the timing of your model operations.
				profiler.profile_operations(options=opts)
				# profiler.advise()
	return

def test_mobileV2_mnist():
	# Create the model
	data_format = "NHWC"
	model = mnist_model.MobileNetV2_mnist(data_format, batch_size=batch_size)

	y_ = tf.placeholder(tf.float32, [batch_size, 10])
	with tf.name_scope('loss'):
		cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=y_, logits=model.output)
		cross_entropy = tf.reduce_mean(cross_entropy)

	# for bn
	update_ops = tf.get_collection(tf.GraphKeys.UPDATE_OPS)

	profiler = tf.profiler.Profiler(tf.get_default_graph())

	with tf.control_dependencies(update_ops):
		with tf.name_scope('adam_optimizer'):
			train_op = tf.train.AdamOptimizer(1e-3).minimize(cross_entropy)

	with tf.name_scope('accuracy'):
		correct_prediction = tf.equal(tf.argmax(model.output, 1), tf.argmax(y_, 1))
		correct_prediction = tf.cast(correct_prediction, tf.float32)
		acc = tf.reduce_mean(correct_prediction, name="acc")

	x = np.zeros([batch_size, 784], np.float32)
	labels = np.zeros([batch_size, 10], np.float32)

	config = tf.ConfigProto()
	# config.gpu_options.allow_growth = True
	# config.gpu_options.per_process_gpu_memory_fraction = 0.75
	with tf.Session(config = config) as sess:
		sess.run(tf.global_variables_initializer())
		# profiler = tf.profiler.Profiler(sess.graph)
		options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
		opts = tf.profiler.ProfileOptionBuilder.time_and_memory()
		run_meta = tf.RunMetadata()

		for i in range(max_iter):
			sess.run(train_op, options=options, run_metadata=run_meta,
							 feed_dict={model.is_training: True,
													model.x: x, y_: labels })
			# sess.run(acc, options=options, run_metadata=run_meta,
			#            feed_dict={model.is_training: False,
			#                       model.x: x, y_: labels})
			profiler.add_step(i, run_meta)
			profiler.profile_operations(options=opts)
	return

if __name__ == '__main__':
	main()
	# parser = argparse.ArgumentParser()
	# parser.add_argument('--data_dir', type=str,
	#                     default='/tmp/tensorflow/mnist/input_data',
	#                     help='Directory for storing input data')
	# FLAGS, unparsed = parser.parse_known_args()
	# tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
