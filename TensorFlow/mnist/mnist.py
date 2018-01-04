
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import argparse
import sys

from tensorflow.examples.tutorials.mnist import input_data

import tensorflow as tf

FLAGS = None

def NN(imgs, keep_prob) :

  init = tf.contrib.layers.xavier_initializer(dtype = tf.float32)
  with tf.name_scope('fc1') :
    W_fc1 = tf.get_variable("W_fc1", shape=[784, 30], initializer=init)
    b_fc1 = tf.get_variable("b_fc1", shape=[30], initializer=init)
    h_fc1 = tf.nn.relu(tf.matmul(imgs, W_fc1) + b_fc1)

  with tf.name_scope('dropout1') :
    h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

  with tf.name_scope('fc2') :
    W_fc2 = tf.get_variable("W_fc2", shape=[30, 10], initializer=init)
    b_fc2 = tf.get_variable("b_fc2", shape=[10], initializer=init)
    logits = tf.nn.relu(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)

  # with tf.name_scope('dropout2') :
    # h_fc2_drop = tf.nn.dropout(h_fc2, keep_prob)

  # with tf.name_scope('fc3') :
    # W_fc3 = tf.get_variable("W_fc3", shape=[20, 10], initializer=init)
    # b_fc3 = tf.get_variable("b_fc3", shape=[10], initializer=init)
    # logits = tf.nn.relu(tf.matmul(h_fc2_drop, W_fc3) + b_fc3)
  return logits
    

def main(_):
  # training param
  learning_rate = 1e-4 # 0.5
  max_iter = 40000
  train_batch_size = 500
  display_step = 20
  
  # test_batch_size = 500
  # test_iter = 20
  test_interval = 60

  # Import data
  mnist = input_data.read_data_sets("MNIST_data/", one_hot=True, 
                                    source_url='http://yann.lecun.com/exdb/mnist/')

  # Create the model
  imgs = tf.placeholder(tf.float32, [None, 784])
  labels = tf.placeholder(tf.float32, [None, 10])
  keep_prob = tf.placeholder(tf.float32)
  
  logits = NN(imgs, keep_prob)
  
  with tf.name_scope('accuracy'):
    correct_prediction = tf.equal(tf.argmax(logits, 1), tf.argmax(labels, 1))
    correct_prediction = tf.cast(correct_prediction, tf.float32)
    accuracy = tf.reduce_mean(correct_prediction)
  
  # The raw formulation of cross-entropy,
  #
  #   tf.reduce_mean(-tf.reduce_sum(y_ * tf.log(tf.nn.softmax(y)),
  #                                 reduction_indices=[1]))
  #
  # can be numerically unstable.
  #
  # So here we use tf.losses.sparse_softmax_cross_entropy on the raw
  # outputs of 'y', and then average across the batch.
  # cross_entropy = tf.losses.sparse_softmax_cross_entropy(labels=y_, logits=y)
  
  with tf.name_scope('loss') : 
    cross_entropy = tf.nn.softmax_cross_entropy_with_logits(labels=labels, logits=logits)
    cross_entropy = tf.reduce_mean(cross_entropy)
  
  with tf.name_scope('adam_optimizer') :
    train_step = tf.train.AdamOptimizer(learning_rate).minimize(cross_entropy)
    # train_step = tf.train.GradientDescentOptimizer(learning_rate).minimize(cross_entropy)
  

  # sess = tf.InteractiveSession()
  # tf.global_variables_initializer().run()
  # Train
  with tf.Session() as sess :
    sess.run(tf.global_variables_initializer())
    for i in range(max_iter):
      # test
      if i % test_interval == 0 and i != 0 :
        # batch_imgs, batch_labels = mnist.test.next_batch(test_batch_size)
        batch_imgs, batch_labels = mnist.test.images, mnist.test.labels
        test_accuracy = accuracy.eval(feed_dict={imgs: batch_imgs, labels: batch_labels, 
                                    keep_prob: 1.0})
        print("  step {} test accuracy {}".format(i, test_accuracy))
      # train
      batch_imgs, batch_labels = mnist.train.next_batch(train_batch_size)
      if i % display_step == 0 and i != 0 :
        x_entropy = cross_entropy.eval(feed_dict={imgs: batch_imgs, labels: batch_labels,
                                    keep_prob: 0.5})
        print("iter {} - x_entropy: {}".format(i, x_entropy))
      else :
        train_step.run(feed_dict={imgs: batch_imgs, labels: batch_labels,
                                    keep_prob: 0.5})
    
  # Test trained model
  # correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(labels, 1))
  # accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
  # print(sess.run(accuracy, feed_dict={x: mnist.test.images,
                                      # labels: mnist.test.labels}))

if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('--data_dir', type=str, default='/tmp/tensorflow/mnist/input_data',
                      help='Directory for storing input data')
  FLAGS, unparsed = parser.parse_known_args()
  tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
