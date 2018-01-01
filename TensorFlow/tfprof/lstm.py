
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys

from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf
from tensorflow.contrib import rnn

FLAGS = None
n_input = 28 # MNIST data input (img shape: 28*28)
n_steps = 28 # timesteps
n_hidden = 50 # hidden layer num of features
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
    
    batch_size = 1
    time_steps = 1
    num_features = 8

    # cell = rnn.BasicLSTMCell(n_hidden, forget_bias=1.0)
    # cell = rnn.BasicLSTMCell(n_hidden)
    # cell = rnn.LSTMCell(n_hidden)
    cell = rnn.GRUCell(n_hidden)
    # print(cell.state_size)
    
    n_input = 100
    n_steps = 1
    # print(n_steps * n_input)
    inputs = tf.placeholder(tf.float32, [batch_size, n_steps * n_input])
    print(inputs)
    return 
    h0 = cell.zero_state(batch_size, tf.float32)
    output, h1 = cell.call(inputs, h0)

    tf.profiler.profile(
        tf.get_default_graph(), options=tf.profiler.ProfileOptionBuilder.float_operation())


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--data_dir', type=str, default='/tmp/tensorflow/mnist/input_data',
                        help='Directory for storing input data')
    FLAGS, unparsed = parser.parse_known_args()
    tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
