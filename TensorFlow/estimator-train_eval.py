import tensorflow as tf
from tensorflow import layers
import tensorflow.contrib as tc
import tensorflow.contrib.learn as tcl

import simple_model as smodel
import dataset

def main():
  train_dir = r'F:\Lab408\jinzhengu\root\resized\train'
  eval_dir = r'F:\Lab408\jinzhengu\root\resized\eval'
  model_dir = r'F:\Lab408\jinzhengu\root\tb_log'
  
  eval_interval = 50
  
  save_summary_steps = 10
  save_checkpoints_steps = 25
  train_batchsz = 20
  eval_batchsz = 20
  eval_steps = 40
  epoch = 30
  img_num = 1105
  max_steps = (img_num * epoch) // train_batchsz

  # input fn
  dset = dataset.MyDataset(train_dir, eval_dir)
  # train_x, train_y, train_fname = dset.train(batch_sz=10, prefetch_batch=3)
  # eval_x, eval_y, eval_fname = dset.eval(train_batchsz, prefetch_batch=4)
  
  # train_in_fn = lambda : [train_x, train_y]
  # eval_in_fn = lambda : [eval_x, eval_y]
  def train_in_fn(dset, batch_sz=20, prefetch_batch=None):
    train_x, train_y, train_fname = dset.train(batch_sz, prefetch_batch)
    train_x.set_shape([batch_sz, 200, 250, 3])
    return train_x, train_y
  def eval_in_fn(dset, batch_sz, prefetch_batch=4):
    eval_x, eval_y, eval_fname = dset.eval(batch_sz, prefetch_batch)
    eval_x.set_shape([batch_sz, 200, 250, 3])
    return eval_x, eval_y

  # run config
  session_config = tf.ConfigProto()
  session_config.gpu_options.allow_growth = True
  session_config.gpu_options.per_process_gpu_memory_fraction = 0.75
  run_conf = tf.estimator.RunConfig(
      model_dir=model_dir,
      save_summary_steps=save_summary_steps,
      save_checkpoints_steps=save_checkpoints_steps,
      session_config=session_config
  )

  est = tf.estimator.Estimator(model_fn = model_fn,
      config= run_conf, params= {
        'data_format': 'NHWC'
      })
  # Experiment
  expt = tcl.Experiment(
    estimator= est,
    train_input_fn= lambda : train_in_fn(dset, train_batchsz),
    eval_input_fn= lambda : eval_in_fn(dset, eval_batchsz, prefetch_batch=None),
    train_steps= max_steps,
    eval_steps= eval_steps,
    min_eval_frequency= save_checkpoints_steps*2,
  )

  expt.train_and_evaluate()

  # estimator
  # classifier = tf.estimator.Estimator(model_fn = model_fn,
  #     config= run_conf, params= {
  #       'data_format': 'NHWC'
  #     })
  # classifier.train(input_fn= lambda : train_in_fn(dset), steps= eval_interval)
  # classifier.evaluate(input_fn= lambda : eval_in_fn(dset, eval_batchsz))

  # while True:
  # # #   # eval every step train
  #   classifier.train(input_fn= lambda : train_in_fn(), steps= eval_interval)
    # classifier.evaluate(input_fn= lambda : eval_in_fn(), steps= eval_iter)

  print("end")
  return
# end main

def model_fn(features, labels, mode, params):
  """The model_fn argument for creating an Estimator."""
  # model
  model = smodel.Simplest(params['data_format'])
  img = features
  if isinstance(img, dict):
    img = features['image']

  logits = model(img, mode == tf.estimator.ModeKeys.TRAIN)
  _pred = tf.argmax(logits, axis=1, output_type=tf.int32)

  train_op = None
  if (mode == tf.estimator.ModeKeys.TRAIN or
      mode == tf.estimator.ModeKeys.EVAL):
     # If we are running multi-GPU, we need to wrap the optimizer.
    # if params.get('multi_gpu'):
      # optimizer = tf.contrib.estimator.TowerOptimizer(optimizer)
    
    loss = tf.losses.sparse_softmax_cross_entropy(
        labels=labels, logits=logits)
    # https://stackoverflow.com/questions/48241370/estimator-train-with-num-steps-in-tensorflow?rq=1
    acc = tf.metrics.accuracy(
        labels=labels, predictions=_pred)
    # Name the accuracy tensor 'train_accuracy' to demonstrate the
    # LoggingTensorHook.
    tf.identity(acc[1], name='train_accuracy')
    tf.summary.scalar('train_accuracy', acc[1])

    # acc_mat = tf.equal(labels, _pred)
    # acc = tf.reduce_mean(tf.cast(acc_mat, tf.float32))
    # tf.summary.scalar('accuracy', acc)
    predictions = None
    export_outputs = None
  else :
    loss = None

  if mode == tf.estimator.ModeKeys.TRAIN :
    train_op = tf.train.AdamOptimizer(1e-4).minimize(
      loss, tf.train.get_or_create_global_step()
    )
  elif mode == tf.estimator.ModeKeys.PREDICT:
    predictions = {
      'classes': _pred,
      'prob': tf.nn.softmax(logits, name='softmax_tensor')
    }
    export_outputs = {
      'classify': tf.estimator.export.PredictOutput(predictions)
    }
    # end main body before return
  spec = tf.estimator.EstimatorSpec(
    mode= mode, predictions= predictions,
    loss=loss, train_op=train_op,
    export_outputs= export_outputs
  )
  return spec
# end model_fn

# def train_in_fn(train_x, train_y):

if __name__ == '__main__':
  # a, b, c = 1, 2, 3
  # fn = lambda : [a, b, c]
  # infn = lambda : fn()
  # a += 1
  # b += 1
  # c += 1
  # print(infn())
  # print("before main")
 main()