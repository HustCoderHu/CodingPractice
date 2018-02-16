import os
import os.path as path
import tensorflow as tf

class MyDataset():
  def __init__(self, train_dir, eval_dir, resize=None):
    if not path.exists(train_dir):
      raise SystemError('directory not exist: {}'.format(
        train_dir ))
    if not path.exists(eval_dir):
      raise SystemError('directory not exist: {}'.format(
        eval_dir ))

    self.train_dir = train_dir
    self.eval_dir = eval_dir
    self.resize=resize

    self.dict_name_id = {}
    labels = os.listdir(train_dir)
    for idx, name in enumerate(labels):
      self.dict_name_id[name] = idx
  
  def train(self, batch_sz = 10, prefetch_batch=None):
    print('train ----------')
    return self._get(self.train_dir, batch_sz, prefetch_batch)
  
  def eval(self, batch_sz = 10, prefetch_batch=None):
    print('eval ===========')
    return self._get(self.eval_dir, batch_sz, prefetch_batch,
        repeat=False)


  def _get(self, subset_dir, batch_sz, prefetch_batch=None, repeat=True):
    labels = os.listdir(subset_dir)
    img_list = []
    label_list = []
    for class_name in labels:
      per_class_dir = path.join(subset_dir, class_name)
      per_class_imglist = os.listdir(per_class_dir)
      print('{}: total {}'.format(class_name, len(per_class_imglist)))
      _list = [path.join(per_class_dir, i) for i in per_class_imglist]
      img_list.extend(_list)
      label_list.extend(
          [self.dict_name_id[class_name]] * len(per_class_imglist))
    
    print('images num: {}'.format(len(img_list)))
    t_imglist = tf.constant(img_list)
    t_lbllist = tf.constant(label_list, dtype=tf.int32)
    dataset = tf.data.Dataset().from_tensor_slices((t_imglist, t_lbllist))
    if self.resize == None:
      dset = dataset.map(self._mapfn, num_parallel_calls=os.cpu_count())
    else :
      dset = dataset.map(self._mapfn_resize, num_parallel_calls=os.cpu_count())
    dset = dset.shuffle(len(img_list), reshuffle_each_iteration=False)
    
    if prefetch_batch == None:
      dset = dset.cache()
    if repeat:
      dset = dset.repeat()
    dset = dset.batch(batch_sz)
    if prefetch_batch != None:
      dset = dset.prefetch(prefetch_batch)
    # img, label, filename
    # shape (batch_sz, )
    return dset.make_one_shot_iterator()
    # return dset.make_one_shot_iterator().get_next()
    # _iter = dset.make_one_shot_iterator()
    # next_one = _iter.get_next()
    # return next_one
  
  # end _get()

  def _mapfn(self, filename, label):
    with tf.device('/cpu:0'):
      # <https://www.tensorflow.org/performance/performance_guide>
      img_raw = tf.read_file(filename)
      decoded = tf.image.decode_bmp(img_raw)
      decoded = tf.cast(decoded, tf.float32)
    return decoded, label, filename
  
  def _mapfn_resize(self, filename, label):
    with tf.device('/cpu:0'):
      # <https://www.tensorflow.org/performance/performance_guide>
      img_raw = tf.read_file(filename)
      decoded = tf.image.decode_bmp(img_raw)
      _h, _w = self.resize
      resized = tf.image.resize_images(decoded, [_h, _w])
    return resized, label, filename

def ___get(self, sub_dir):
  labels = os.listdir(dir)
  # class_id = [i for i in len(labels)]

  img_list = []
  label_list = []
  for class_id, class_name in enumerate(labels):
    per_class_dir = path.join(dir, class_name)
    per_class_imglist = os.listdir(per_class_dir)
    print('{}: total {}'.format(class_name, len(per_class_imglist)))
    _list = [path.join(per_class_dir, i) for i in per_class_imglist]
    img_list.extend(_list)
    label_list.extend([class_id] * len(per_class_imglist))
  
  print('images num: {}'.format(len(img_list)))

  t_imglist = tf.constant(img_list)
  t_lbllist = tf.constant(label_list)

  dataset = tf.data.Dataset().from_tensor_slices(t_imglist, t_lbllist)
  dset = dataset.map(_mapfunc, num_parallel_calls=os.cpu_count())
  dset = dset.shuffle(len(img_list), reshuffle_each_iteration=False)
  dset = dset.repeat()
  return dset

# print(tf.test.gpu_device_name()) # /device:GPU:0

# dir = r'F:\Lab408\jinzhengu\root\resized_train'
# train(dir)