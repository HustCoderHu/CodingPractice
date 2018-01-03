
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys
import time
import numpy as np
import pylab 

import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

# from tensorflow.contrib import rnn
import tensorflow.contrib.rnn as rnn
from tensorflow.python.client import timeline

FLAGS = None
data_dir = "MNIST_data/"


def weight_variable(shape) :
  """weight_variable generates a weight variable of a given shape."""
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape) :
  """bias_variable generates a bias variable of a given shape."""
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)
  
def RNN(rnntype, inputs, n_hidden, n_classes) :
  # print(inputs.shape[0])
  # print(inputs.shape[1])
  # print(inputs.shape[2])
  # batch_size = int(inputs.shape[0])
  
  print(inputs[0].shape[1])
  state_size = int(inputs[0].shape[1])
  
  # for dynamic
  # n_steps = int(inputs.shape[1])
  # state_size = int(inputs.shape[2])
  # print(type(state_size))
  
  if rnntype == "GRU" :
    print("rnntype: " + rnntype)
    cell = rnn.GRUCell(n_hidden)
  else :
    print("rnntype: " + rnntype)
    cell = rnn.LSTMCell(n_hidden)

  # initial_state = cell.zero_state(batch_size, tf.float32)
  outputs, state = tf.nn.static_rnn(cell, inputs, dtype = tf.float32)
  #initial_state=initial_state)
  # outputs, state = tf.nn.dynamic_rnn(cell, inputs, initial_state=initial_state)
  output = outputs[-1] # final output
  print(output.shape)

  with tf.name_scope('logits_vec') :
    w = weight_variable([n_hidden, n_classes])
    b = weight_variable([n_classes])
 
  # output_mat = tf.reshape(output, [-1, state_size])
  logits = tf.matmul(output, w) + b
    
  return logits

  
def main(_):
  rnntype = "GRU"
  # net param
  n_input = 28 # MNIST data input (img shape: 28*28)
  n_steps = 28 # timesteps
  n_hidden = 70 #50 # hidden layer num of features
  n_classes = 10 # MNIST total classes (0-9 digits)
  
  # training param
  learning_rate = 1e-3
  max_iter = 40000
  train_batch_size = 500
  display_step = 20
  
  # test_batch_size = 500
  # test_iter = 20
  test_interval = 60
  

  mnist = input_data.read_data_sets(data_dir, one_hot=True, 
                                  source_url='http://yann.lecun.com/exdb/mnist/')
  batch_imgs, batch_labels = mnist.train.next_batch(1)
  # print(batch_imgs)
  # print(batch_labels)

  # print("input: ")
  # print(mnist.train.images)
  # print("input shape: ")
  # print(mnist.train.images.shape)
  
  # display one img
  # im = mnist.train.images[1]
  # im = im.reshape(-1,28)
  # pylab.imshow(im)
  # pylab.show()
  
  # inputs = tf.placeholder(tf.float32, [None, n_steps, n_input])
  inputs = tf.placeholder(tf.float32, [None, n_steps*n_input])
  y = tf.placeholder(tf.float32, [None, n_classes])
  # print(inputs.shape)
  # print(inputs.shape[2])
  inputs_list = []
  inputs_list.append(inputs)
  logits = RNN(rnntype, inputs_list, n_hidden, n_classes)
  
  # output = RNN(rnntype, inputs, n_hidden, n_classes)

  with tf.name_scope('accuracy'):
    correct_prediction = tf.equal(tf.argmax(logits, 1), tf.argmax(y, 1))
    correct_prediction = tf.cast(correct_prediction, tf.float32)
    accuracy = tf.reduce_mean(correct_prediction)

  with tf.name_scope('loss') : 
    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=logits)
    cross_entropy = tf.reduce_mean(cross_entropy)
  
  with tf.name_scope('adam_optimizer') :
    train_step = tf.train.AdamOptimizer(learning_rate).minimize(cross_entropy)
  
  config = tf.ConfigProto()
  # config.gpu_options.allow_growth = True
  with tf.Session(config = config) as sess :
    sess.run(tf.global_variables_initializer())
    for i in range(max_iter) :
      # test
      if i % test_interval == 0 and i != 0 :
        # batch_imgs, batch_labels = mnist.test.next_batch(test_batch_size)
        batch_imgs, batch_labels = mnist.test.images, mnist.test.labels
        test_accuracy = accuracy.eval(feed_dict={inputs: batch_imgs, y: batch_labels})
        print("  step {} test accuracy {}".format(i, test_accuracy))
      # train
      batch_imgs, batch_labels = mnist.train.next_batch(train_batch_size)
      if i % display_step == 0 and i != 0 :
        x_entropy = cross_entropy.eval(feed_dict={inputs: batch_imgs, y: batch_labels})
        print("x_entropy: {}".format(x_entropy))
      else :
        train_step.run(feed_dict={inputs: batch_imgs, y: batch_labels})
    
  return

  # tf.profiler.profile(
      # tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())
  # return 
  # np.zero, np.one
  feed2input = np.full((train_batch_size,  n_steps, n_input), 0.)
  
  # with tf.Session(config=tf.ConfigProto(log_device_placement=True)) as sess :
  config = tf.ConfigProto()
  config.gpu_options.allow_growth = True
  with tf.Session(config = config) as sess:
    sess.run(tf.global_variables_initializer())
    
    # add additional options to trace the session execution
    # options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
    # run_metadata = tf.RunMetadata()
    
    # start = time.perf_counter()
    sess.run([output, h1], feed_dict={inputs: feed2input}, 
                    options=options, run_metadata=run_metadata)
    
    # Create the Timeline object, and write it to a json file
    # fetched_timeline = timeline.Timeline(run_metadata.step_stats)
    # chrome_trace = fetched_timeline.generate_chrome_trace_format()
    # with open('input10k_gru_i3-4160.json', 'w') as f:
        # f.write(chrome_trace)
    # elapsed = time.perf_counter() - start
  # print(result)
  print('\n')
  # print('Elapsed %.6f seconds.' % elapsed)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_dir', type=str, default='/tmp/tensorflow/mnist/input_data',
                        help='Directory for storing input data')
    FLAGS, unparsed = parser.parse_known_args()
    tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
