import sys
import os
import os.path as path
import json
import numpy as np

from tensorflow.examples.tutorials.mnist import input_data
import tensorflow as tf
from tensorflow import layers

cwd = os.getcwd()
sys.path.append(cwd)
import mnist_model

mnist_dir = r"E:\github_repo\tftest\mnist"
model_dir = path.join(mnist_dir, "model")
SavedModel_dir = path.join(mnist_dir, "SavedModel")
data_dir = path.join(mnist_dir, "MNIST_data")



def main():
  # test_mobileV2_mnist()
  # test_mobileV2_mnist(profile=True)
  # default_lenet()
  test_fcn_lenet()

  return

def test_fcn_lenet() :
  # Create the model
  data_format = "NHWC"
  model = mnist_model.fcn_lenet(data_format)
  # Define loss and optimizer
  # Build the graph for the deep net
  
  # with tf.name_scope('accuracy'):
  #   correct_prediction = tf.equal(tf.argmax(model.output, 1), tf.argmax(y_, 1))
  #   correct_prediction = tf.cast(correct_prediction, tf.float32)
  #   acc = tf.reduce_mean(correct_prediction, name="acc")

  # Add ops to save and restore all the variables.
  saver = tf.train.Saver()

  # Import data
  mnist = input_data.read_data_sets(data_dir, one_hot=True,
                                    source_url=
                                    'http://yann.lecun.com/exdb/mnist/')
  
  signature_key = 'test_signature'
  input_key = 'x_'
  output_key = 'output'
  # mnist.test.labels type: ndarray  
  test_size = mnist.test.labels.shape[0]
  # print(type(model.output))
  batch_size = 50
  
  config = tf.ConfigProto()
  # config.gpu_options.allow_growth = True
  config.gpu_options.per_process_gpu_memory_fraction = 0.75
  with tf.Session(config=config) as sess:
    # restore model
    # meta_graph_def = tf.saved_model.loader.load(sess, ['tag_string'], SavedModel_dir)
    # signature = meta_graph_def.signature_def
    # # 从signature中找出具体输入输出的tensor name 
    # x_tensor_name = signature[signature_key].inputs[input_key].name
    # y_tensor_name = signature[signature_key].outputs[output_key].name
    # # 获取tensor 并inference
    # x = sess.graph.get_tensor_by_name(x_tensor_name)
    # y = sess.graph.get_tensor_by_name(y_tensor_name)
    y = tf.placeholder(dtype=tf.float32, shape=[batch_size, 10])
    y_ = tf.placeholder(dtype=tf.float32, shape=[batch_size, 10])
    with tf.name_scope("correct_count"):
      correct_pred = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
      correct_pred = tf.cast(correct_pred, tf.int32)
      n_correct = tf.reduce_sum(correct_pred, name="correct_count")
    # print("aaa")
    # print(type(n_correct))
    # print(n_correct.shape)

    # # begin test
    iteration = int(test_size / batch_size)
    remaining = test_size % batch_size
    acc_array = np.zeros([iteration + (remaining != 0)], np.int32)
    for i in range(iteration):
      batch = mnist.test.next_batch(batch_size)
      count = sess.run(n_correct, feed_dict = {x: batch[0], y_: batch[1]})
      print("iter {}: ".format(i))
      print("  accuracy: %g" % count / batch_size)
      acc_array[i] = count
    if remaining != 0:
      mnist.test.next_batch(remaining)
      count = sess.run(n_correct, feed_dict = {x: batch[0], y_: batch[1]})
      print("iter {}: ".format(i))
      print("  accuracy: %g" % count / remaining)
      acc_array[-1] = count

    # print(acc_array.size)
    whole_acc = np.sum(acc_array) / acc_array.size
    print('whole val set accuracy %g' % whole_acc)
  return

if __name__ == '__main__':
  main()
  # parser = argparse.ArgumentParser()
  # parser.add_argument('--data_dir', type=str,
  #                     default='/tmp/tensorflow/mnist/input_data',
  #                     help='Directory for storing input data')
  # FLAGS, unparsed = parser.parse_known_args()
  # tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
