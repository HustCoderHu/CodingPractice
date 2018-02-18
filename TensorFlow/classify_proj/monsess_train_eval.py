import time
import os
import os.path as path
import tensorflow as tf

import dataset
import simple_model as smodel
import runhooks


def main():

  train_dir = r'F:\Lab408\jinzhengu\root\shuffled_divided\train'
  eval_dir = r'F:\Lab408\jinzhengu\root\shuffled_divided\eval'
  log_dir = r'F:\Lab408\jinzhengu\root\monitored_sess_log'
  ckpt_dir = path.join(log_dir, 'ckpts')
  # model_dir = r'F:\Lab408\jinzhengu\root\monitored_sess_log'
  
  eval_interval = 20
  
  save_summary_steps = 5
  save_ckpts_steps = 100
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
  inputx = tf.transpose(inputx, [0, 3, 1, 2]) # nchw
  # eval_x.set_shape([eval_batchsz, 200, 250, 3])

  # train_x, train_y, train_fname = dset.train(train_batchsz, prefetch_batch)
  # train_x.set_shape([train_batchsz, 200, 250, 3])
  # eval_x, eval_y, eval_fname = dset.eval(eval_batchsz, prefetch_batch)
  # eval_x.set_shape([eval_batchsz, 200, 250, 3])

  # \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ build graph \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
  model = smodel.Simplest('NCHW')
  # model = smodel.Simplest('NHWC')
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
  

  # ||||||||||||||||||||||||||||||  hooks ||||||||||||||||||||||||||||||
  # >>>  logging
  tf.logging.set_verbosity(tf.logging.INFO)
  # global_step = tf.train.get_or_create_global_step()
  # tf.identity(global_step, 'g_step')
  # tf.identity(loss, 'cross_entropy')
  # tf.identity(acc, 'accuracy')
  # tensor_lr = optimizer._lr_t

  tensors = {
    'step': tf.train.get_or_create_global_step().name,
    'loss': loss.name,
    'accuracy': acc.name
  }
  logging_hook = tf.train.LoggingTensorHook(
    tensors= tensors,
    every_n_iter=10
  )

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
  # merged_op = tf.summary.merge_all()
  # summary_hook = tf.train.SummarySaverHook(
  #   save_steps=1,
  #   output_dir= ckpt_dir,
  #   summary_op= merged_op
  # )
  
  # >>> main run hook
  eval_hook = runhooks.RunHook(
    iter_dict= iter_dict,
    eval_steps= eval_interval,
    train_op= train_op,
    training= model.training,
    holder_handle= holder_handle,
    summary_conf= summary_conf,
    summary_protobuf= summary_protobuf,
  )

  # >>>  checkpoit saver
  ckpt_saver_hook = runhooks.CkptSaverHook(
    ckpt_dir,
    save_steps= save_ckpts_steps
  )
  # ckpt_saver_hook = tf.train.CheckpointSaverHook(
  #   checkpoint_dir= ckpt_dir,
  #   save_steps= save_ckpts_steps,
  # )

  all_hooks = [
      # logging_hook,
      # summary_hook,
      eval_hook,
      ckpt_saver_hook,
      # tf.train.StopAtStepHook(max_steps),
      # tf.train.NanTensorHook(loss)
  ]

  # ////////////////////////////// session config //////////////////////////////
  sess_conf = tf.ConfigProto()
  sess_conf.gpu_options.allow_growth = True
  sess_conf.gpu_options.per_process_gpu_memory_fraction = 0.75
  
  sess_creator = tf.train.ChiefSessionCreator(
      # scaffold=scaffold,
      # master='',
      config=sess_conf,
      checkpoint_dir=ckpt_dir
  )
  # print('end')
  # return

  # ------------------------------  start  ------------------------------
  with tf.train.MonitoredSession(
    session_creator= sess_creator,
    hooks= all_hooks,
    stop_grace_period_secs= 3600
    ) as mon_sess:
    while not mon_sess.should_stop():
      step = mon_sess.run(tf.train.get_global_step()) # arg from retval of _EvalHook before_run()
      # training, step = mon_sess.run([model.training, tf.train.get_global_step()]) # arg from retval of _EvalHook before_run()
      # if not training:
        # print('step {}: eval xxxxxxxxx'.format(step))
      # print(lr)
  return




if __name__ == '__main__':
  main()

