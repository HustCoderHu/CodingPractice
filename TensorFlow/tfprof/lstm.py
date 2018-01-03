
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
n_input = 28 # MNIST data input (img shape: 28*28)
n_steps = 28 # timesteps
n_hidden = 2 #50 # hidden layer num of features
n_classes = 10 # MNIST total classes (0-9 digits)

def main(_):

    # t=0  t=1    t=2  t=3     t=4
    # [The, brown, fox, is,     quick]
    # [The, red,   fox, jumped, high]
    # words_in_dataset = [0, 1, 2, 3, 4]
    # words_in_dataset[0] = ["THE", "The"]
    # words_in_dataset[1] = ["brown", "red"]
    # words_in_dataset[2] = ["fox", "fox"]
    # words_in_dataset[3] = ["is", "jumped"]
    # words_in_dataset[4] = ["quick", "high"]
    
    batch_size = 3
    time_steps = 1
    num_features = 8

    # cell = rnn.BasicLSTMCell(n_hidden, forget_bias=1.0)
    # cell = rnn.BasicLSTMCell(n_hidden)
    # cell = rnn.LSTMCell(n_hidden)
    cell = rnn.GRUCell(n_hidden)
    # print(cell.state_size)
    
    n_input = 10000
    n_steps = 1
    # print(n_steps * n_input)
    # input = tf.placeholder(tf.float32, [batch_size, n_input])
    
    initial_state = cell.zero_state(batch_size, tf.float32)
    
    # output, h1 = cell.call(inputs, initial_state)
    
    # inputs = tf.placeholder(tf.float32, [time_steps, batch_size, n_input])
    # outputs, states = rnn.static_rnn(cell, inputs, dtype=tf.float32)
    
    batch_size = 3
    num_steps = 100
    features = n_input = 10
    initial_state = cell.zero_state(batch_size, tf.float32)
    inputs = tf.placeholder(tf.float32, [batch_size, num_steps, features])
    outputs, states = 
        
    # print(initial_state)
    print(inputs)
    # print(h1)
    print(outputs)
    
    number_of_layers = 3
    stacked_lstm = rnn.MultiRNNCell([rnn.LSTMCell(n_hidden) for _ in range(number_of_layers)])
    
    initial_state = state = stacked_lstm.zero_state(batch_size, tf.float32)
    return 

    # tf.profiler.profile(
        # tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())
    # return 
    # np.zero, np.one
    feed2input = np.full((batch_size, n_steps * n_input), 0.)
    
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
