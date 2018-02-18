import tensorflow as tf
from tensorflow import layers
import tensorflow.contrib as tc

def main():
  print('end')

  model = Simplest('NHWC')
  print(model.layer_data_format)
  inputs = tf.constant(1.0, shape=[50, 200, 250, 3])
  logits = model(inputs, training=False)

  return

class Simplest:
  def __init__(self, data_format='NHWC', dtype=tf.float32):
    self.data_format = data_format
    self.dtype = dtype
    self.layer_data_format = 'channels_last' if data_format == 'NHWC' \
        else 'channels_first'
    self.training = tf.placeholder(tf.bool, [])
    return

  def __call__(self, inputs):
    # self.training
    pr_shape = lambda var : print(var.shape)

    out = self.layer_conv2d(inputs, n_out=64, kernel_sz=7, strides=4, activation=tf.nn.relu6)
    # out = self.layer_conv2d(out, 64, kernel_sz=5, strides=3, activation=tf.nn.relu6)
    # pr_shape(out)
    out = self.layer_maxpool(out, pool_sz=4, strides=4)
    # pr_shape(out)
    # out = self.layer_conv2d(out, 32, kernel_sz=3, strides=2, activation=tf.nn.relu6)
    # out = self.layer_conv2d(out, 64, kernel_sz=3, strides=2, activation=tf.nn.relu6)
    # out = self.layer_maxpool(out, pool_sz=4, strides=4)
    # pr_shape(out)

    out = self.fc(out, 2)
    # out = tf.layers.dropout(out, training=self.training)
    # out = self.fc(out, 2)
    # out = self.layer_conv2d(out, 10, kernel_sz=3, strides=2, activation=tf.nn.relu6)
    # pr_shape(out)
    
    # out = self.layer_conv2d(out, 128, activation=tf.nn.relu6)
    # out = self.dw_conv3x3(out)
    # out = tf.nn.relu6(out)
    # out = self.layer_conv2d(out, 2)

    # out = self.global_avg_pool(out)
    # pr_shape(out)
    return out
  
  def layer_conv2d(self, x, n_out, kernel_sz=1, strides=1, padding='same',
        activation=None, use_bias=False):
    w_initer=tc.layers.xavier_initializer(dtype=self.dtype)
    if use_bias:
      out = tf.layers.conv2d(x, n_out, kernel_sz, strides=stride,
              padding=padding, data_format=self.layer_data_format,
              activation=activation, use_bias=True,
              kernel_initializer=w_initer, bias_initializer=w_initer)
    else :
      out = tf.layers.conv2d(x, n_out, kernel_sz, strides=strides,
              padding=padding, data_format=self.layer_data_format,
              activation=activation, use_bias=False,
              kernel_initializer=w_initer)
    return out
  
  def dw_conv3x3(self, x, strides=1):
    w_initer=tc.layers.xavier_initializer(dtype=self.dtype)
    if self.data_format == 'NHWC':
      n_in = x.shape[-1]
      strides_4d = [1, strides, strides, 1]
    else :
      n_in = x.shape[1]
      strides_4d = [1, 1, strides, strides]
    channel_multiplier = 1
    w3x3 = tf.get_variable('w3x3', [3, 3, n_in, channel_multiplier],
            initializer=w_initer)
    out = tf.nn.depthwise_conv2d(x, w3x3, strides=strides_4d,
            padding='SAME', data_format=self.data_format)
    return out
  
  def fc(self, x, n_out):
    if len(x.shape) == 4:
      size_per_batch = x.shape[1] * x.shape[2] * x.shape[3]
      x = tf.reshape(x, [-1, size_per_batch])
    w_initer=tc.layers.xavier_initializer(dtype=self.dtype)
    out = tf.layers.dense(x, n_out, activation=None,
                            use_bias=False, kernel_initializer=w_initer)
    return out
  
  def layer_maxpool(self, x, pool_sz, strides):
    out = tf.layers.max_pooling2d(x, pool_size=pool_sz,
        strides=strides, padding='same',
        data_format=self.layer_data_format)
    return out

  def global_avg_pool(self, x):
    if self.data_format == 'NHWC':
      out = tf.reduce_mean(x, (1, 2))
    else :
      out = tf.reduce_mean(x, (2, 3))
    return out

# end class Simplest

# if __name__ == '__main__':
#   main()