
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys
import time
import numpy as np
import os
import json
import matplotlib.pyplot as plt

from concurrent.futures import ProcessPoolExecutor
from concurrent.futures import ThreadPoolExecutor

import tensorflow as tf
# from tensorflow.contrib import rnn
# import tensorflow.nn
import tensorflow.contrib.rnn as rnn
from tensorflow.python.client import timeline


FLAGS = None

def main(argv=None):
  if argv is None:
    argv = sys.argv
    argc = len(argv)
  draw_flops_curve()
  return


def draw_flops_curve() :
  rnntype_l = ["GRU", "LSTM"]
  nInput_l = []
  for i in range(1, 4):
    nInput_l.append(500 * i)
  print(nInput_l)

  n_hidden = 50
  n_steps = 30
  n_classes = 10

  flops_dict = {}
  result = {}
  for type in rnntype_l:
    flops_dict[type] = {}
    result[type] = {}

  max_workers = len(rnntype_l) * len(nInput_l) # ThreadPoolExecutor
  max_workers = os.cpu_count()                 # ProcessPoolExecutor
  # Process faster
  # ThreadPoolExecutor ProcessPoolExecutor
  with ProcessPoolExecutor(max_workers) as executor:
    for type in rnntype_l:
      for n_input in nInput_l:
        param_l = [type, n_input, n_hidden, n_steps, n_classes]
        # flops = get_flops(param_l)
        result[type][n_input] = executor.submit(get_flops, param_l)
    executor.shutdown()
    print("-------------------------------------")

  for type in rnntype_l :
    for n_input in nInput_l :
      print("flops: {}".format(result[type][n_input].result()))
      flops_dict[type][n_input] = result[type][n_input].result()
  print("-------------------------------------")

  # print(str(flops_dict))
  with open('flops_curve.json', 'w') as f:
    json.dump(flops_dict, f)

  # draw the curve
  # figureIdx = 1
  plt.title('n_steps: {}, n_hidden: {}'.format(n_steps, n_hidden))
  for type in rnntype_l :
    # plt.figure(figureIdx)
    # plt.title(type)
    # figureIdx = figureIdx + 1
    plt.ylabel('float operations / million')
    plt.xlabel('input')
    flops_struct = {'nInput_l': [], 'flops': []}
    for n_input in nInput_l :
      flops_struct['nInput_l'].append(n_input)
      flops_struct['flops'].append(flops_dict[type][n_input] / 1e6)
    plt.plot(flops_struct['nInput_l'], flops_struct['flops'],
             linestyle='-', label = type)
  plt.legend(loc='lower right')
  plt.show()

  return

def get_flops(param_list) :
  param_idx = 0
  rnntype = param_list[param_idx]
  param_idx = param_idx + 1
  n_input = param_list[param_idx]
  param_idx = param_idx + 1
  n_hidden = param_list[param_idx]  # hidden layer num of features
  param_idx = param_idx + 1
  n_steps = param_list[param_idx]
  param_idx = param_idx + 1
  n_classes = param_list[param_idx] # MNIST total classes (0-9 digits)

  print(rnntype)
  print(n_input)
  print(n_hidden)
  print(n_steps)
  print(n_classes)

  batch_size = 1

  feed2input = np.full((batch_size, n_steps, n_input), 0.)

  flops = 0
  g = tf.Graph()
  with g.as_default() :
    inputs = tf.placeholder(tf.float32, [batch_size, n_steps, n_input])
    output = RNN(rnntype, inputs, n_hidden, n_classes)
    options = tf.profiler.ProfileOptionBuilder.float_operation()
    options['output'] = ''
    prof = tf.profiler.profile(g, cmd = 'op', options = options)
    # print(type(prof))
    print(prof.total_float_ops)
    flops = prof.total_float_ops
    # tf.profiler.profile(tf.get_default_graph(),
    #                     options=tf.profiler.ProfileOptionBuilder.float_operation())
  return flops

def get_trace_dict(argv) :
  # platform = "i3-4160"
  # platform = "1080ti"
  # net param
  # n_input = 500 # 500 1000
  # n_input = int(argv[1])
  # argv_idx = 1
  # rnntype = str(argv[argv_idx])
  # argv_idx = argv_idx + 1
  # n_input = int(argv[argv_idx])
  # argv_idx = argv_idx + 1
  # n_hidden = int(argv[argv_idx])

  rnntype = "GRU"
  n_input = 1000
  n_hidden = 50  # hidden layer num of features
  n_steps = 30
  # n_classes = 10 # MNIST total classes (0-9 digits)

  argv_idx = 2
  if argc >= argv_idx:
    rnntype = str(argv[argv_idx])
    argv_idx = argv_idx + 1

  if argc >= argv_idx:
    n_input = int(argv[argv_idx])
    argv_idx = argv_idx + 1

  if argc >= argv_idx:
    n_hidden = int(argv[argv_idx])
    argv_idx = argv_idx + 1

  if argc >= argv_idx:
    n_steps = int(argv[argv_idx])
    argv_idx = argv_idx + 1

  print(rnntype)
  print(n_input)
  print(n_hidden)
  print(n_steps)

  # training param
  batch_size = 1

  inputs = tf.placeholder(tf.float32, [batch_size, n_steps, n_input])

  # rnntype = "LSTM"
  # rnntype = "GRU"
  output = RNN(rnntype, inputs, n_hidden)

  # tf.profiler.profile(
  # tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())
  # return
  # np.zero, np.one
  feed2input = np.full((batch_size, n_steps, n_input), 0.)

  os.environ['CUDA_VISIBLE_DEVICES'] = '-1'
  config = tf.ConfigProto(device_count={"CPU": 1, "GPU": 0},
                          allow_soft_placement=True,
                          log_device_placement=False)
  # config.gpu_options.allow_growth = True
  with tf.Session(config=config) as sess:
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
    print(type(chrome_trace))


    # file = rnntype + "_input" + str(n_input) + "_" + platform + ".json"
    # with open(file, 'w') as f:
    #     f.write(chrome_trace)

    # elapsed = time.perf_counter() - start
    # print(result)
    # print('Elapsed %.6f seconds.' % elapsed)
  return

def weight_variable(shape):
  """weight_variable generates a weight variable of a given shape."""
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  """bias_variable generates a bias variable of a given shape."""
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)

def RNN(rnntype, inputs, n_hidden, n_classes=0):
  for i in range(len(inputs.shape)):
    print(inputs.shape[i])

  batch_size = int(inputs.shape[0])
  n_steps = int(inputs.shape[1])
  state_size = int(inputs.shape[2])
  # print(type(state_size))

  if rnntype == "GRU":
    print("rnntype: " + rnntype)
    cell = rnn.GRUCell(n_hidden)
  else:
    print("rnntype: " + rnntype)
    cell = rnn.LSTMCell(n_hidden)
  initial_state = cell.zero_state(batch_size, tf.float32)

  x = tf.unstack(inputs, n_steps, 1)  # [[batch_size, state_size], ...] len = n_steps

  outputs, state = tf.nn.static_rnn(cell, x, initial_state=initial_state)
  output = outputs[-1]  # final output

  # print(len(outputs)) # list len = n_steps
  # print(state)
  # print(output)

  return output

  # with tf.name_scope('logits_vec') :
  #   w = weight_variable([state_size, n_classes])
  #   b = bias_variable([n_classes])
  #
  # output_mat = tf.reshape(output, [-1, state_size])
  # logits = tf.matmul(output_mat, w) + b
  #
  # return logits

if __name__ == '__main__':
  # print(os.getcwd())
  # return
  main()
  # param_list = ["GRU", 1000, 50, 30, 10]
  # get_flops(param_list)
