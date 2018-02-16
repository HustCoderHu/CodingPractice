import time
import os
import os.path as path
import tensorflow as tf

import dataset
import simple_model as smodel


def main():

  train_dir = r'F:\Lab408\jinzhengu\root\resized\train'
  eval_dir = r'F:\Lab408\jinzhengu\root\resized\eval'
  log_dir = r'F:\Lab408\jinzhengu\root\monitored_sess_log'
  ckpt_dir = path.join(log_dir, 'ckpts')
  # model_dir = r'F:\Lab408\jinzhengu\root\monitored_sess_log'
  
  eval_interval = 25
  
  save_summary_steps = 5
  save_ckpts_steps = 20
  train_batchsz = 20
  eval_batchsz = 20
  # eval_steps = 40
  epoch = 30
  img_num = 1105
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
  
  # >>>  eval
  eval_hook = _EvalHook(
    iter_dict= iter_dict,
    eval_steps= eval_interval,
    train_op= train_op,
    training= model.training,
    holder_handle= holder_handle,
    summary_conf= summary_conf,
    summary_protobuf= summary_protobuf,
  )

  # >>>  checkpoit saver
  ckpt_saver_hook = tf.train.CheckpointSaverHook(
    checkpoint_dir= ckpt_dir,
    save_steps= save_ckpts_steps,
  )

  all_hooks = [
      # logging_hook,
      # summary_hook,
      # eval_hook,
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
      training, step = mon_sess.run([model.training, tf.train.get_global_step()]) # arg from retval of _EvalHook before_run()
      # if not training:
        # print('step {}: eval xxxxxxxxx'.format(step))
      # print(lr)
  return



class _EvalHook(tf.train.SessionRunHook):
  def __init__(self,
    iter_dict,
    eval_steps,
    train_op,
    training,
    holder_handle,
    summary_conf,
    summary_protobuf,
  ):
    """
    args:
    - iter_dict
        {'train': dataset.make_iter, 'eval': same}
    - summary_conf
        dict {'dir': dir, 'saved_steps': int}
    - summary_protobuf dict:
        'name' -> protobuf returned by tf.summary.x (x in scalar, hisogram etc)
    """
    self.tensor_handle = {
      'train': iter_dict['train'].string_handle(),
      'eval': iter_dict['eval'].string_handle()
    }
    self.iter_dict = iter_dict
    self.eval_steps_ = eval_steps
    self.eval_marker = True
    self.train_op_ = train_op
    self.training_ = training
    self.holder_handle_ = holder_handle
    self.summary_save_steps = summary_conf['saved_steps']

    # summary
    train_summary = path.join(summary_conf['dir'], 'train')
    eval_summary = path.join(summary_conf['dir'], 'eval')

    self.summary_writer_= {
      'train': tf.summary.FileWriterCache.get(train_summary),
      'eval':  tf.summary.FileWriterCache.get(eval_summary)
    }
    self.merged_summary_ = tf.summary.merge(list(summary_protobuf.values()))
    return
  
  def begin(self):
    self.global_step_tensor_ = tf.train.get_or_create_global_step()
    # pylint: disable=protected-access
    if self.global_step_tensor_ is None:
      raise RuntimeError(
          "Global step should be created to use _EvalHook.")
    # self._start_time = time.time()
    return
  
  def after_create_session(self, session, coord):
    self.global_step = session.run(self.global_step_tensor_)
    # print('global step: {}'.format(self.global_step))
    self.train_handle = session.run(
        self.tensor_handle['train'])
    self.eval_handle = session.run(
        self.tensor_handle['eval'])

  def before_run(self, run_context):
    # print('self.global_step: {}'.format(self.global_step))
    request = {'summary_str': self.merged_summary_}
    if self.global_step % self.eval_steps_ == 0 :
      feed_dict={
        self.holder_handle_: self.eval_handle,
        self.training_: False
      }
    else:
      request['train_op'] = self.train_op_
      feed_dict={
        self.holder_handle_: self.train_handle,
        self.training_: True
      }
    return tf.train.SessionRunArgs(fetches= request,
        feed_dict= feed_dict)

  def after_run(self, run_context, run_values):
    # run_values type tf.train.SessionRunValues
    req_dict = run_values.result
    # [1] tensorflow.core.protobuf.config_pb2.RunOptions
    # [2] tensorflow.core.protobuf.config_pb2.RunMetadata
    if self.global_step % self.eval_steps_ == 0 \
        and self.eval_marker :
      self.summary_writer_['eval'].add_summary(
        req_dict['summary_str'], self.global_step)
      self.eval_marker = False
    else :
      if self.global_step % self.summary_save_steps == 0 :
        self.summary_writer_['train'].add_summary(
          req_dict['summary_str'], self.global_step)
      self.global_step += 1
      self.eval_marker = True
  
  def end(self, session):
    self.summary_writer_['train'].flush()
    self.summary_writer_['eval'].flush()
# end class _EvalHook

if __name__ == '__main__':
  main()

