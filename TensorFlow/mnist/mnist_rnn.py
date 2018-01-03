
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
# import tensorflow.nn
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
  
def RNN(inputs, n_hidden, n_classes) :
  print(inputs.shape[0])
  print(inputs.shape[1])
  print(inputs.shape[2])
  batch_size = int(inputs.shape[0])
  state_size = int(inputs.shape[2])
  # print(type(state_size))
  
  # cell = rnn.LSTMCell(n_hidden)
  cell = rnn.GRUCell(n_hidden)
  initial_state = cell.zero_state(batch_size, tf.float32)
  outputs, state = tf.nn.dynamic_rnn(cell, inputs, initial_state=initial_state)
  output = outputs[-1] # final output

  with tf.name_scope('logits_vec') :
    w = weight_variable([state_size, n_classes])
    b = weight_variable([n_classes])
 
  output_mat = tf.reshape(output, [-1, state_size])
  logits = tf.matmul(output_mat, w) + b
    
  return logits

  
def main(_):
  # net param
  n_input = 28 # MNIST data input (img shape: 28*28)
  n_steps = 28 # timesteps
  n_hidden = 20 #50 # hidden layer num of features
  n_classes = 10 # MNIST total classes (0-9 digits)
  
  # training param
  learning_rate = 1e-3
  max_iter = 1000
  test_interval = 5
  train_batch_size = 50
  display_step = 50

  mnist = input_data.read_data_sets(data_dir, one_hot=True, 
                                  source_url='http://yann.lecun.com/exdb/mnist/')
  # print("input: ")
  # print(mnist.train.images)
  # print("input shape: ")
  # print(mnist.train.images.shape)
  
  # display one img
  # im = mnist.train.images[1]
  # im = im.reshape(-1,28)
  # pylab.imshow(im)
  # pylab.show()
  
  inputs = tf.placeholder(tf.float32, [8, n_steps, n_input])
  y = tf.placeholder(tf.float32, [None, n_classes])
  # print(inputs.shape)
  # print(inputs.shape[2])
  
  logits = RNN(inputs, n_hidden, n_classes)

  with tf.name_scope('accuracy'):
    correct_prediction = tf.equal(tf.argmax(logits, 1), tf.argmax(y, 1))
    correct_prediction = tf.cast(correct_prediction, tf.float32)
    accuracy = tf.reduce_mean(correct_prediction)

  with tf.name_scope('loss') : 
    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=y, logits=logits)
    cross_entropy = tf.reduce_mean(cross_entropy)
  
  with tf.name_scope('adam_optimizer'):
    train_step = tf.train.AdamOptimizer(learning_rate).minimize(cross_entropy)
  
  config = tf.ConfigProto()
  # config.gpu_options.allow_growth = True
  with tf.Session(config = config) as sess :
    sess.run(tf.global_variables_initializer())
    for i in range(max_iter) :
      batch_imgs, batch_labels = mnist.train.next_batch(train_batch_size)
      if i % 100 == 0 and i != 0 :
        train_accuracy = accuracy.eval(feed_dict={x: batch_imgs, y: batch_labels})
        print('step %d, training accuracy %g' % (i, train_accuracy))
      train_step.run(feed_dict={x: batch_imgs, y: batch_labels})
      
      if 
  
  return
  
  # cell = rnn.BasicLSTMCell(n_hidden, forget_bias=1.0)
  # cell = rnn.BasicLSTMCell(n_hidden)
  # cell = rnn.LSTMCell(n_hidden)
  cell = rnn.GRUCell(n_hidden)
  # print(cell.state_size)
  initial_state = cell.zero_state(train_batch_size, tf.float32)
  # inputs = tf.placeholder(tf.float32, [time_steps, train_batch_size, n_input])
  # outputs, states = rnn.static_rnn(cell, inputs, dtype=tf.float32)
  
  # train_batch_size
  num_steps = 28
  features = n_input = 28
  
  # outputs, states = rnn.
  # print(initial_state)
  print(inputs)
  # print(h1)
  print(outputs)
  
  number_of_layers = 3
  stacked_lstm = rnn.MultiRNNCell([rnn.LSTMCell(n_hidden) for _ in range(number_of_layers)])
  
  initial_state = state = stacked_lstm.zero_state(train_batch_size, tf.float32)
  return 
  
  # tf.profiler.profile(
      # tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())
  # return 
  # np.zero, np.one
  feed2input = np.full((train_batch_size, n_steps * n_input), 0.)
  
  # with tf.Session(config=tf.ConfigProto(log_device_placement=True)) as sess :
  with tf.Session() as sess :
    sess.run(tf.global_variables_initializer())
    
    # add additional options to trace the session execution
    options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
    run_metadata = tf.RunMetadata()
    
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
