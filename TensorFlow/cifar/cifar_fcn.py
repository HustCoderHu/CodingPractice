import tensorflow as tf
from tensorflow import layers
import tensorflow.contrib as tc

def main():
  # Create the model
  x = tf.placeholder(tf.float32, [None, 784])

  # Define loss and optimizer
  # y_ = tf.placeholder(tf.int64, [None])
  y_ = tf.placeholder(tf.float32, [None, 10])

  # y_conv, keep_prob = lenet(x)

  # Create the model
  model = MobileNetV2_mnist()
  return

class fcn_lenet():
  def __init__(self, data_format="NCHW", batch_size=0, input_size=28):
    self.data_format = data_format
    # self.data_format = "NHWC"
    self.input_size = input_size
    # self.normalizer = tc.layers.batch_norm
    with tf.variable_scope("mnist"):
      if batch_size != 0:
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[batch_size, 784])
      else:
        self.x = tf.placeholder(dtype=tf.float32,
                                shape=[None, 784])
      self.output = self._build_model(self.x)
    return

  def build_graph(self):
    """Build a whole graph for the model."""
    self.global_step = tf.train.get_or_create_global_step()
    self._build_model()
    if self.mode == "train":
      self._build_train_op()
    self.summaries = tf.summary.merge_all()
    return

  def _build_model(self, x):
    init = tc.layers.xavier_initializer(dtype=tf.float32)
    data_format = "channels_first" if self.data_format == "NCHW" \
      else "channels_last"
    with tf.name_scope('reshape'):
      if self.data_format == "NCHW":
        x_image = tf.reshape(x, [-1, 1, 28, 28])
      else:
        x_image = tf.reshape(x, [-1, 28, 28, 1])
    with tf.name_scope("conv1_relu") :
      knl_size = 5
      n_out = 32
      out = tf.layers.conv2d(x_image, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=tf.nn.relu, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    # Pooling layer - downsamples by 2X.
    with tf.name_scope("pool1") :
      out = tf.layers.max_pooling2d(out, pool_size=2, strides=2,
                                    padding="same",
                                    data_format=data_format)
    # Second convolutional layer -- maps 32 feature maps to 64.
    with tf.name_scope("conv2_relu") :
      knl_size = 3
      n_out = 64
      out = tf.layers.conv2d(out, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=tf.nn.relu, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    # Second pooling layer.
    with tf.name_scope("pool2") :
      out = tf.layers.max_pooling2d(out, pool_size=2, strides=2,
                                    padding="same",
                                    data_format=data_format)
    with tf.name_scope("depthwise_relu6") :
      n_in = n_out
      channel_multiplier = 1
      strides_4d = [1, 1, 1, 1]
      w3x3 = tf.get_variable("dw3x3", [3, 3, n_in, channel_multiplier],
                             initializer=init)
      out = tf.nn.depthwise_conv2d(out, w3x3, strides=strides_4d, 
          padding="SAME", data_format=self.data_format)
      out = tf.nn.relu6(out)
      # out = layers.conv2d(out, 64, 3, strides=1, padding='same',
      #     data_format=data_format, use_bias=False, kernel_initializer=init)

    with tf.name_scope("pointwise") :
      knl_size = 1
      n_out = 10
      out = tf.layers.conv2d(out, n_out, knl_size, strides=1,
                             padding="same", data_format=data_format,
                             activation=None, use_bias=True,
                             kernel_initializer=init,
                             bias_initializer=init)
    pool_size = out.shape[2:4] if self.data_format == "NCHW" \
      else out.shape[1:3]
    with tf.name_scope("global_avg_pool") :
      out = tf.layers.average_pooling2d(out, pool_size, strides=1,
                                        data_format=data_format)
    out = tf.reshape(out, [-1, 10])
    return out

  def _build_train_op(self):
    return
if __name__ == '__main__':
  main()

# reference
# https://github.com/timctho/mobilenet-v2-tensorflow/blob/master/models.py
# https://github.com/tonylins/pytorch-mobilenet-v2/blob/master/MobileNetV2.py

# BN
# http://blog.csdn.net/FontThrone/article/details/76652772
# http://www.liulizhe.com/2017/09/12/cnn%E4%B8%AD%E7%9A%84batch-normalization%E5%8F%8A%E5%85%B6tensorflow%E7%94%A8%E6%B3%95/