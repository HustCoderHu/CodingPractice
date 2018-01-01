
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys

from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf

FLAGS = None


def main(_):

    # t=0  t=1    t=2  t=3     t=4
    # [The, brown, fox, is,     quick]
    # [The, red,   fox, jumped, high]
    words_in_dataset = [0, 1, 2, 3, 4]
    words_in_dataset[0] = ["THE", "The"]
    words_in_dataset[1] = ["brown", "red"]
    words_in_dataset[2] = ["fox", "fox"]
    words_in_dataset[3] = ["is", "jumped"]
    words_in_dataset[4] = ["quick", "high"]
    batch_size = 2
    time_steps = 5
    num_features = 8

    # Create the model
    words_in_dataset = tf.placeholder(tf.float32,
                                      [time_steps, batch_size, num_features])
    lstm_size = 1
    lstm = tf.contrib.rnn.BasicLSTMCell(lstm_size)
    # Initial state of the LSTM memory.
    hidden_state = tf.zeros([batch_size, lstm.state_size])
    current_state = tf.zeros([batch_size, lstm.state_size])
    state = hidden_state, current_state
    probabilities = []
    loss = 0.0
    for current_batch_of_words in words_in_dataset:
        # The value of state is updated after processing each batch of words.
        output, state = lstm(current_batch_of_words, state)

        # The LSTM output can be used to make next word predictions
        logits = tf.matmul(output, softmax_w) + softmax_b
        probabilities.append(tf.nn.softmax(logits))
        loss += loss_function(probabilities, target_words)

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
