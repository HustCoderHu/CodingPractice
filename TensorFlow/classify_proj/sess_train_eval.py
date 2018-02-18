import time
import os
import os.path as path
import tensorflow as tf

import dataset
import simple_model as smodel


def main():

  train_dir = r'F:\Lab408\jinzhengu\root\shuffled_divided\train'
  eval_dir = r'F:\Lab408\jinzhengu\root\shuffled_divided\eval'
  log_dir = r'F:\Lab408\jinzhengu\root\session_log'
  ckpt_dir = path.join(log_dir, 'ckpts')
  # model_dir = r'F:\Lab408\jinzhengu\root\monitored_sess_log'
  
  eval_interval = 20
  
  save_summary_steps = 5
  save_ckpts_steps = 20
  train_batchsz = 20
  eval_batchsz = 50
  # eval_steps = 40
  epoch = 900
  img_num = 870 * 2
  max_steps = (img_num * epoch) // train_batchsz


  # ------------------------------ prepare input ------------------------------
  dset = dataset.MyDataset(train_dir, eval_dir)
  prefetch_batch = None
  iter_dict = {
    'train': dset.train(train_batchsz, prefetch_batch),
    'eval': dset.eval(eval_batchsz, prefetch_batch)
  }

  # train_iter = dset.train(train_batchsz, prefetch_batch)
  # eval_iter = dset.eval(eval_batchsz, prefetch_batch)
  # dict_tsr_handle = {
    # 'train': train_iter.string_handle(),
    # 'eval': eval_iter.string_handle()
  # }

  holder_handle = tf.placeholder(tf.string, [])
  iter = tf.data.Iterator.from_string_handle(
      holder_handle, iter_dict['train'].output_types)
  # next_elem = iter.get_next()
  inputx, labels, filename = iter.get_next()
  inputx = tf.reshape(inputx, [-1, 200, 250, 3])
  # eval_x.set_shape([eval_batchsz, 200, 250, 3])

  # train_x, train_y, train_fname = dset.train(train_batchsz, prefetch_batch)
  # train_x.set_shape([train_batchsz, 200, 250, 3])
  # eval_x, eval_y, eval_fname = dset.eval(eval_batchsz, prefetch_batch)
  # eval_x.set_shape([eval_batchsz, 200, 250, 3])

  # \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ build graph \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  model = smodel.Simplest('NHWC')
  logits = model(inputx)
  with tf.name_scope('cross_entropy'):
    loss = tf.losses.sparse_softmax_cross_entropy(labels, logits)
    
  with tf.name_scope('accuracy'):
    _pred = tf.argmax(logits, axis=1, output_type=tf.int32)
    acc_vec = tf.equal(labels, _pred)
    acc = tf.reduce_mean(tf.cast(acc_vec, tf.float32))
    
  with tf.name_scope('optimizer'):
    optimizer = tf.train.AdamOptimizer(1e-4)
    train_op = optimizer.minimize(loss, tf.train.get_or_create_global_step())
  

  # >>>  summary
  summary_conf = {
    'dir': log_dir,
    'saved_steps': save_summary_steps
  }
  summary_protobuf = {
    'loss': tf.summary.scalar('cross_entropy', loss),
    'accuracy': tf.summary.scalar('accuracy', acc)
  }
  # print(list(summary_protobuf.values()))
  # summary_loss = tf.summary.scalar('cross_entropy', loss)
  # summary_acc = tf.summary.scalar('accuracy', acc)
  # summary_lr = tf.summary.scalar('lr', optimizer._lr_t)
  # global_step = 
  merged_op = tf.summary.merge_all()
  # summary_hook = tf.train.SummarySaverHook(
  #   save_steps=1,
  #   output_dir= ckpt_dir,
  #   summary_op= merged_op
  # )
  
  # >>>  eval

  op_init1 = tf.variables_initializer(tf.global_variables())
  op_init2 = tf.variables_initializer(tf.local_variables())
  op_group = tf.group(op_init1, op_init2)

  # ////////////////////////////// session config //////////////////////////////
  sess_conf = tf.ConfigProto()
  sess_conf.gpu_options.allow_growth = True
  sess_conf.gpu_options.per_process_gpu_memory_fraction = 0.75
  
  train_writer = tf.summary.FileWriter(path.join(summary_conf['dir'], 'train'))
  eval_writer = tf.summary.FileWriter(path.join(summary_conf['dir'], 'eval'))

  summary_timer = tf.train.SecondOrStepTimer(every_steps=save_summary_steps)
  eval_timer = tf.train.SecondOrStepTimer(every_steps=eval_interval)
  with tf.Session(config= sess_conf) as sess:
    train_handle = sess.run(iter_dict['train'].string_handle())
    eval_handle = sess.run(iter_dict['eval'].string_handle())

    sess.run(op_group)
    for _step in range(max_steps):
      if eval_timer.should_trigger_for_step(_step):
        summary_str = sess.run(merged_op, feed_dict= {
          holder_handle: eval_handle,
          model.training: False
        })
        eval_writer.add_summary(summary_str, _step)
        eval_timer.update_last_triggered_step(_step)
      
      summary_str, _ = sess.run([merged_op, train_op], feed_dict={
        holder_handle: train_handle,
        model.training: True
      })
      if summary_timer.should_trigger_for_step(_step):
        train_writer.add_summary(summary_str, _step)
        summary_timer.update_last_triggered_step(_step)

  print('end')
  return

if __name__ == '__main__':
  main()

