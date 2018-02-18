from os.path import join as pjoin

import tensorflow as tf
import tensorflow.contrib as tc

def main():
  export_dir = r'D:\github_repo\CodingPractice\TensorFlow\export_dir'
  max_steps = 8

  inputx = tf.placeholder(tf.float32, [None, 1])
  print(inputx.dtype)
  labels = tf.placeholder(tf.int32, [None, 1])
  out = fc(inputx, 8)
  logits = fc(out, 2)

  with tf.name_scope('cross_entropy'):
    loss = tf.losses.sparse_softmax_cross_entropy(labels, logits)
  with tf.name_scope('optimizer'):
    optimizer = tf.train.AdamOptimizer(1e-4)
    train_op = optimizer.minimize(loss, tf.train.get_or_create_global_step())

  op_init1 = tf.variables_initializer(tf.global_variables())
  op_init2 = tf.variables_initializer(tf.local_variables())
  op_group = tf.group(op_init1, op_init2)

  builder = tf.saved_model.builder.SavedModelBuilder(export_dir)
  # ////////////////////////////// session config //////////////////////////////
  sess_conf = tf.ConfigProto()
  sess_conf.gpu_options.allow_growth = True
  sess_conf.gpu_options.per_process_gpu_memory_fraction = 0.75
  
  with tf.Session(config= sess_conf) as sess:
    sess.run(op_group)
    builder.add_meta_graph_and_variables(
      sess,
      [tf.saved_model.tag_constants.TRAINING],
      # signature_def_map=foo_signatures,
      # assets_collection=foo_assets
    )
    cond = True
    for i in range(max_steps):
      sess.run(train_op, feed_dict={inputx: [[i/4]]*3, labels: [[i//4]]*3})
      print('step %d' %i)
      if cond:
        builder.save()

  print('main() end')
    

def fc(x, n_out):
  # size_per_batch = x.shape[1]
  # x = tf.reshape(x, [-1, size_per_batch])
  w_initer=tc.layers.xavier_initializer(dtype=tf.float32)
  out = tf.layers.dense(x, n_out, activation=None,
                          use_bias=False, kernel_initializer=w_initer)
  return out

if __name__ == '__main__':
  main()