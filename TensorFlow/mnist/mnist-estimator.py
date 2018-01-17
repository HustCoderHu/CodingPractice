import sys
import os
import numpy as np
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

def input(dataset):
 return dataset.images, dataset.labels.astype(np.int32)

def main(args):
  print(args)
  # training param
  learning_rate = 1e-4 # 0.5
  max_iter = 40000
  train_batch_size = 500
  display_step = 20
  
  # test_batch_size = 500
  # test_iter = 20
  test_interval = 60
  tftest_dir = args[0] # E:\github_repo\tftest
  mnist_dir = os.path.join(tftest_dir, "MNIST_data")
  # Import data
  if not os.path.exists(mnist_dir):
    print("not exist: ".format(mnist_dir))
    return

  mnist = input_data.read_data_sets(mnist_dir, source_url='http://yann.lecun.com/exdb/mnist/')
  # print(type(mnist.train)) # DataSet
  # print(type(mnist.train.images)) # numpy.ndarray
  # print(type(mnist.train.labels)) # numpy.ndarray

  mnist_model_dir = os.path.join(tftest_dir, "mnist_model")
  feature_columns = [tf.feature_column.numeric_column("x", shape = [28, 28])]
  classifier = tf.estimator.DNNClassifier(
    feature_columns=feature_columns,
    hidden_units=[256, 32],
    optimizer=tf.train.AdamOptimizer(1e-4),
    n_classes=10,
    dropout=0.1,
    model_dir=mnist_model_dir
  )

  train_input_fn = tf.estimator.inputs.numpy_input_fn(
    x = {"x": input(mnist.train)[0]},
    y = input(mnist.train)[1],
    num_epochs = None,
    batch_size = 50,
    shuffle = True
  )
  classifier.train(input_fn=train_input_fn, steps=60000)

  test_input_fn = tf.estimator.inputs.numpy_input_fn(
    x = {"x": input(mnist.test)[0]},
    y = input(mnist.test)[1],
    num_epochs = 1,
    shuffle = False
  )
  accuracy_score = classifier.evaluate(input_fn=test_input_fn)["accuracy"]
  print("\nTest Accuracy: {0:f}%\n".format(accuracy_score * 100))

if __name__ == '__main__':
  main(sys.argv[1:])

# reference
# https://codeburst.io/use-tensorflow-dnnclassifier-estimator-to-classify-mnist-dataset-a7222bf9f940
# https://gist.github.com/marcolanaro/67b77346730c0862b17c4800ee599286#file-mnist_estimator-py