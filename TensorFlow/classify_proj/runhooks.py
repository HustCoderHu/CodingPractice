from os.path import join as pjoin
import tensorflow as tf
from tensorflow import logging

class RunHook(tf.train.SessionRunHook):
  """
  interleave  train and eval, periodly save summary
  """
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
    - iter_dict: 'dict'
        {'train': dataset.make_iter, 'eval': same}
    - summary_conf: 'dict'
        {'dir': dir, 'saved_steps': int}
    - summary_protobuf: 'dict'
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
    train_summary = pjoin(summary_conf['dir'], 'train')
    eval_summary = pjoin(summary_conf['dir'], 'eval')

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
          "Global step should be created to use EvalHook.")
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
    req_dict = run_values.results
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

class CkptSaverHook(tf.train.SessionRunHook):
  def __init__(self,
    ckpt_dir,
    save_steps=None,
    save_secs=None,
    ckpt_basename='model.ckpt'
  ):
    self.ckpt_dir_ = ckpt_dir
    self.save_path_ = pjoin(ckpt_dir, ckpt_basename)
    self.timer_ = tf.train.SecondOrStepTimer(every_secs=save_secs,
        every_steps=save_steps)
    return
  
  def begin(self):
    self.global_step_tensor_ = tf.train.get_or_create_global_step()
    if self.global_step_tensor_ is None:
      raise RuntimeError(
          "Global step should be created to use CkptSaverHook.")
    return

  def before_run(self, run_context):
    return tf.train.SessionRunArgs(self.global_step_tensor_)
  
  def after_run(self, run_context, run_values):
    stale_global_step = run_values.results
    if self.timer_.should_trigger_for_step(stale_global_step+1):
      # get the real value after train op.
      global_step = run_context.session.run(self.global_step_tensor_)
      if self.timer_.should_trigger_for_step(global_step):
        self.timer_.update_last_triggered_step(global_step)
        self._save(run_context.session, global_step)
    return
  
  def end(self, session):
    last_step = session.run(self.global_step_tensor_)
    if last_step != self.timer_.last_triggered_step():
      self._save(session, last_step)
    return

  def _save(self, session, step):
    """Saves the latest checkpoint."""
    logging.info("Saving checkpoints for %d into %s.",
        step, self.save_path_)
    self._get_saver().save(session, self.save_path_, global_step=step)
    return

  def _get_saver(self):
    # Get saver from the SAVERS collection if present.
    # collection_key = ops.GraphKeys.SAVERS
    # savers = ops.get_collection(collection_key)
    collection_key = tf.GraphKeys.SAVERS
    savers = tf.get_collection(collection_key)
    if not savers:
      raise RuntimeError(
          "No items in collection {}. Please add a saver to the collection "
          "or provide a saver or scaffold.".format(collection_key))
    elif len(savers) > 1:
      raise RuntimeError(
          "More than one item in collection {}. "
          "Please indicate which one to use by passing it to the constructor.".
          format(collection_key))

    self._saver = savers[0]
    return savers[0]
# end class CkptSaverHook