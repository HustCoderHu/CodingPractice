
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys
import time
import numpy as np

import tensorflow as tf

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
  
def RNN(rnntype, inputs, n_hidden, n_classes) :
  for i in range(len(inputs.shape)) :
    print(inputs.shape[i])

  batch_size = int(inputs.shape[0])
  n_steps = int(inputs.shape[1])
  state_size = int(inputs.shape[2])
  # print(type(state_size))
  
  if rnntype == "GRU" :
    print("rnntype: " + rnntype)
    cell = rnn.GRUCell(n_hidden)
  else :
    print("rnntype: " + rnntype)
    cell = rnn.LSTMCell(n_hidden)
  initial_state = cell.zero_state(batch_size, tf.float32)
  
  x = tf.unstack(inputs, n_steps, 1) # [[batch_size, state_size], ...] len = n_steps
  
  outputs, state = tf.nn.static_rnn(cell, x, initial_state=initial_state)
  output = outputs[-1] # final output
  
  # print(len(outputs)) # list len = n_steps
  # print(state)
  # print(output)
  
  return output

  with tf.name_scope('logits_vec') :
    w = weight_variable([state_size, n_classes])
    b = weight_variable([n_classes])
 
  output_mat = tf.reshape(output, [-1, state_size])
  logits = tf.matmul(output_mat, w) + b
    
  return logits

  
def main(argv=None):
  if argv is None:
    argv = sys.argv

  # platform = "i3-4160"
  platform = "1080ti"
  
  # net param
  n_input = 500 # 500 1000
  n_input = int(argv[1])
  print(n_input)
  
  n_steps = 30
  n_hidden = 50 # hidden layer num of features
  n_classes = 10 # MNIST total classes (0-9 digits)
  
  # training param
  batch_size = 1
  
  inputs = tf.placeholder(tf.float32, [batch_size, n_steps, n_input])
  
  # rnntype = "LSTM"
  rnntype = "GRU"
  output = RNN(rnntype, inputs, n_hidden, n_classes)
 
  tf.profiler.profile(
      tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())
  return
  # np.zero, np.one
  feed2input = np.full((batch_size, n_steps, n_input), 0.)
  
  # with tf.Session(config=tf.ConfigProto(log_device_placement=True)) as sess :
  config = tf.ConfigProto()
  config.gpu_options.allow_growth = True
  with tf.Session(config = config) as sess:
    sess.run(tf.global_variables_initializer())
    
    # add additional options to trace the session execution
    options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
    run_metadata = tf.RunMetadata()
    
    # start = time.perf_counter()
    sess.run(output, feed_dict={inputs: feed2input}, 
                    options=options, run_metadata=run_metadata)
    
    # Create the Timeline object, and write it to a json file
    fetched_timeline = timeline.Timeline(run_metadata.step_stats)
    chrome_trace = fetched_timeline.generate_chrome_trace_format()
    
    
    file = rnntype + "_input" + str(n_input) + "_" + platform + ".json"
    with open(file, 'w') as f:
        f.write(chrome_trace)
    # elapsed = time.perf_counter() - start
  # print(result)
  print('\n')
  # print('Elapsed %.6f seconds.' % elapsed)

if __name__ == '__main__':
    main()
