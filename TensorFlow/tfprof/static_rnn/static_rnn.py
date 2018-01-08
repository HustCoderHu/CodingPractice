from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys
import time
import numpy as np
import os
import json
# import matplotlib.pyplot as plt

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
  count_op_time_INPUT()
  # op_time_by_STEP()
  # op_time_by_HIDDEN()

  return


def draw_flops_curve():
  rnntype_l = ["GRU", "LSTM"]
  nInput_l = []
  # for i in range(1, 3):
    # nInput_l.append(500 * i)
  nInput_l = [100, 300, 500, 1000]
  # print(nInput_l)

  n_hidden = 50
  n_steps = 30
  n_classes = 10

  flops_dict = {}
  result = {}
  for type in rnntype_l:
    flops_dict[type] = {}
    result[type] = {}

  max_workers = len(rnntype_l) * len(nInput_l)  # ThreadPoolExecutor
  max_workers = os.cpu_count()  # ProcessPoolExecutor
  # Process faster
  # ThreadPoolExecutor ProcessPoolExecutor
  with ProcessPoolExecutor(max_workers) as executor:
    for type in rnntype_l:
      for n_input in nInput_l:
        param_l = [type, n_input, n_hidden, n_steps, n_classes]
        # float_ops = get_float_ops(param_l)
        result[type][n_input] = executor.submit(get_float_ops, param_l)
    executor.shutdown()
    print("-------------------------------------")

  for type in rnntype_l:
    print(type)
    for n_input in nInput_l:
      print("input: {} -- float_ops: {} m".format(n_input, result[type][n_input].result() / 1e6))
      flops_dict[type][n_input] = result[type][n_input].result()
  print("-------------------------------------")

  # print(str(flops_dict))
  return
  # with open('flops_curve.json', 'w') as f:
  #   json.dump(flops_dict, f)

  # draw the curve
  # figureIdx = 1
  plt.title('n_steps: {}, n_hidden: {}'.format(n_steps, n_hidden))
  plt.ylabel('float operations / million')
  plt.xlabel('input')
  for type in rnntype_l:
    # plt.figure(figureIdx)
    # plt.title(type)
    # figureIdx = figureIdx + 1
    x_list = []
    y_list = []
    flops_struct = {'nInput_l': [], 'float_ops': []}
    for n_input in nInput_l:
      x_list.append(n_input)
      y_list.append(flops_dict[type][n_input] / 1e6)
    plt.plot(x_list, y_list, linestyle='-', label=type)
  plt.legend(loc='lower right')
  plt.show()

  return


def get_float_ops(param_list):
  param_idx = 0
  rnntype = param_list[param_idx]
  param_idx = param_idx + 1
  n_input = param_list[param_idx]
  param_idx = param_idx + 1
  n_hidden = param_list[param_idx]  # hidden layer num of features
  param_idx = param_idx + 1
  n_steps = param_list[param_idx]
  param_idx = param_idx + 1
  n_classes = param_list[param_idx]  # MNIST total classes (0-9 digits)

  # print(rnntype)
  # print(n_input)
  # print(n_hidden)
  # print(n_steps)
  # print(n_classes)

  batch_size = 1
  feed2input = np.full((batch_size, n_steps, n_input), 0.)

  float_ops = 0
  g = tf.Graph()
  with g.as_default():
    inputs = tf.placeholder(tf.float32, [batch_size, n_steps, n_input])
    output = RNN(rnntype, inputs, n_hidden, n_classes)

    # count trainable param
    options = tf.profiler.ProfileOptionBuilder.trainable_variables_parameter()
    # prof = tf.profiler.profile(g, cmd='op', options=options)
    # n_param = prof.total_parameters
    n_param = 0

    # count float operations
    options = tf.profiler.ProfileOptionBuilder.float_operation()
    # options['output'] = ''
    prof = tf.profiler.profile(g, cmd='op', options=options) # cmd='scope'
    # print(type(prof))
    # print(prof.total_float_ops)
    float_ops = prof.total_float_ops

  # print(n_param / 1e3)
  # print(float_ops / 1e6)

  return n_param, float_ops


def get_rnn_ops_time(param_list):
  platform = "i3-4160"
  # platform = "1080ti"
  # net param
  param_idx = 0
  rnntype = param_list[param_idx]
  param_idx = param_idx + 1
  n_input = param_list[param_idx]
  param_idx = param_idx + 1
  n_hidden = param_list[param_idx]  # hidden layer num of features
  param_idx = param_idx + 1
  n_steps = param_list[param_idx]
  param_idx = param_idx + 1
  n_classes = param_list[param_idx]  # MNIST total classes (0-9 digits)

  batch_size = 1
  feed2input = np.full((batch_size, n_steps, n_input), 0.)

  g = tf.Graph()
  with g.as_default() :
    inputs = tf.placeholder(tf.float32, [batch_size, n_steps, n_input])
    output = RNN(rnntype, inputs, n_hidden, n_classes)

    # os.environ['CUDA_VISIBLE_DEVICES'] = '-1'
    # config = tf.ConfigProto(device_count={"CPU": 1, "GPU": 0},
    #                         allow_soft_placement=True,
    #                         log_device_placement=False)
    config = tf.ConfigProto()
    # config.gpu_options.allow_growth = True
    with tf.Session(config=config) as sess :
      # start = time.perf_counter()
      sess.run(tf.global_variables_initializer())
      # elapsed = time.perf_counter() - start
      # print('Elapsed %.6f seconds.' % elapsed)

      # add additional options to trace the session execution
      options = tf.RunOptions(trace_level=tf.RunOptions.FULL_TRACE)
      run_metadata = tf.RunMetadata()
      sess.run(output, feed_dict={inputs: feed2input},
               options=options, run_metadata=run_metadata)
      fetched_timeline = timeline.Timeline(run_metadata.step_stats)
      chrome_trace = fetched_timeline.generate_chrome_trace_format()
      # print(type(chrome_trace)) # str
      #
      # file = rnntype + "_input" + str(n_input) + "_" + platform + ".json"
      # with open(file, 'w') as f:
      #     f.write(chrome_trace)

      _dict = json.loads(chrome_trace)
      # print(type(_dict.values()))
      # traceEvents =
      cat_list = []
      _Retval = 0
      for key, traceEvents in _dict.items() :
        # print(key)
        # print(type(traceEvents)) # list
        # print(len(traceEvents))
        # print(val[0])
        for dict in traceEvents :
          if dict['name'] == 'ConcatV2' :
            cat_list.append(dict['ts'])
          if dict['name'] == '_Retval' :
            _Retval = dict['ts']
          # for key, val in dict.items() :
          #   print("{}: {}".format(key, val))
          # break
    # print(_Retval)
    # print(cat_list)
    ops_time = _Retval - min(cat_list)
    print(ops_time)
  return ops_time

def count_params_and_floatops() :
  param_dict = {}
  float_ops_dict = {}
  for type in ['LSTM', 'GRU']:
    param_dict[type] = {}
    float_ops_dict[type] = {}

  hidden_l = [30, 50, 90, 200]
  for type in ['LSTM', 'GRU']:
    for hidden in hidden_l:
      n_param, float_ops = get_float_ops([type, 1000, hidden, 50, 10])
      param_dict[type][hidden] = n_param
      float_ops_dict[type][hidden] = float_ops

  for type, _dict in param_dict.items():
    print(type)
    for hidden, n_param in _dict.items():
      print('hidden: {} -- n_param: {} /k'.format(hidden, n_param / 1e3))

  for type, _dict in float_ops_dict.items():
    print(type)
    for hidden, float_ops in _dict.items():
      print('hidden: {} -- float_ops_dict: {} /m'.format(hidden, float_ops / 1e6))

  return

def count_op_time_INPUT():
  ops_time_dict = {}
  for type in ['LSTM', 'GRU']:
    ops_time_dict[type] = {}

  input_l = [100, 300, 500, 1000]
  hidden = 50
  steps = 30
  for type in ['LSTM', 'GRU']:
    for input in input_l:
      ops_time_l = []
      for _it in range(5):
        ops_time_l.append(get_rnn_ops_time([type, input, hidden, steps, 10]))
      ops_time = 0
      for _time in ops_time_l:
        ops_time = ops_time + _time
      ops_time = ops_time / len(ops_time_l)
      ops_time_dict[type][input] = ops_time

  for type, _dict in ops_time_dict.items():
    print(type)
    for input, ops_time in _dict.items():
      print('input: {} -- ops_time: {} /ms'.format(input, ops_time / 1e3))

def op_time_by_STEP():
  ops_time_dict = {}
  for type in ['LSTM', 'GRU']:
    ops_time_dict[type] = {}

  input = 1000
  hidden = 50
  steps_l = [30, 50, 90, 200]
  for type in ['LSTM', 'GRU']:
    for steps in steps_l:
      ops_time_l = []
      for _it in range(5):
        ops_time_l.append(get_rnn_ops_time([type, input, hidden, steps, 10]))
      ops_time = 0
      for _time in ops_time_l:
        ops_time = ops_time + _time
      ops_time = ops_time / len(ops_time_l)
      ops_time_dict[type][steps] = ops_time

  for type, _dict in ops_time_dict.items():
    print(type)
    for steps, ops_time in _dict.items():
      print('steps: {} -- ops_time: {} /ms'.format(steps, ops_time / 1e3))

def op_time_by_HIDDEN():
  ops_time_dict = {}
  for type in ['LSTM', 'GRU']:
    ops_time_dict[type] = {}

  input = 1000
  hidden_l = [30, 50, 90, 200]
  steps = 50
  for type in ['LSTM', 'GRU']:
    for hidden in hidden_l:
      ops_time_l = []
      for _it in range(5):
        ops_time_l.append(get_rnn_ops_time([type, input, hidden, steps, 10]))
      ops_time = 0
      for _time in ops_time_l:
        ops_time = ops_time + _time
      ops_time = ops_time / len(ops_time_l)
      ops_time_dict[type][hidden] = ops_time

  for type, _dict in ops_time_dict.items():
    print(type)
    for hidden, ops_time in _dict.items():
      print('hidden: {} -- ops_time: {} /ms'.format(hidden, ops_time / 1e3))


def weight_variable(shape):
  """weight_variable generates a weight variable of a given shape."""
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)


def bias_variable(shape):
  """bias_variable generates a bias variable of a given shape."""
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)


def RNN(rnntype, inputs, n_hidden, n_classes=0):
  # for i in range(len(inputs.shape)):
  # print(inputs.shape[i])

  batch_size = int(inputs.shape[0])
  n_steps = int(inputs.shape[1])
  state_size = int(inputs.shape[2])
  # print(type(state_size))

  if rnntype == "GRU":
    # print("rnntype: " + rnntype)
    cell = rnn.GRUCell(n_hidden)
  else:
    # print("rnntype: " + rnntype)
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
  # get_float_ops(param_list)
