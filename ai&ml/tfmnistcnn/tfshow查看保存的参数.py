import tensorflow as tf
reader = tf.train.NewCheckpointReader('./model.ckpt')
dic = reader.get_variable_to_shape_map()
print(dic)

w = reader.get_tensor("Variable_2")
print(type(w))
print(w.shape)
print(w)