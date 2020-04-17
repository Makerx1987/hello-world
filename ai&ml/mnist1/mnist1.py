# 1这句代码from tensorflow.examples.tutorials.mnist import input_data
# 用来在线下载，由于网络问题往往失败，所以手动下载并把压缩文件放到到'MNIST_data'文件夹
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data
# 1 onehot标签，顾名思义，一个长度为n的数组，只有一个元素是1.0，其他元素是0.0。
# 例如在n为4的情况下，标签2对应的onehot标签就是 [0.0 , 0.0  , 1.0 , 0.0]
# 使用onehot的直接原因是现在多分类cnn网络的输出通常是softmax层，而它的输出是一个概率分布，
# 从而要求输入的标签也以概率分布的形式出现，进而算交叉熵之类。
mnisT = input_data.read_data_sets('MNIST_data', one_hot=True)
# 1 placeholder直译为占位者，实际上是数据源x,[None，784 ]表示可以输入任意张784像素点的图
# 2 W权重值，softmax处理层+多个线性回归网络中一条通路就是一个W
# 3 b偏置量，一个线性回归网络一个b
# 4 矩阵乘法tf.matmul
# 5 谷歌已经建好的softmax处理层+多个线性回归网络tf.nn.softmax不包含似然函数，目标函数（损失函数）返回onehot。
# 6 交叉熵代价函数
# 7 谷歌已经建好的tf.train.GradientDescentOptimizer梯度下降函数，步长0.01，目标极大似然函数（交叉熵代价函数）
x = tf.placeholder(tf.float32, [None, 784])
W = tf.Variable(tf.zeros([784, 10]))
b = tf.Variable(tf.zeros([10]))
y = tf.nn.softmax(tf.matmul(x, W) + b)
y_ = tf.placeholder("float", [None, 10])
cross_entropy = -tf.reduce_sum(y_ * tf.log(y))
train_step =\
    tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
# 初始化我们创建的变量，
# 谷歌TensorFlow比较奇怪的地方就是session会话（启动器），当然这在大型项目很方便
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
# 1 模型循环训练1000次（你要训练60000次也可以）
# 2 mnisT.train.next_batch(100)每次取100份1000次覆盖完了
# 3 sess.run启动训练
for i in range(1000):
    batch_xs, batch_ys = mnisT.train.next_batch(100)
    sess.run(train_step, feed_dict={x: batch_xs, y_: batch_ys})
# 1 tf.argmax找到向量最大项编号
# 2 tf.equal匹配
# 3 tf.cast转化数据类型
# 4 tf.reduce_mean一维平均值
correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracy = tf.reduce_mean(tf.cast(correct_prediction, "float"))
print(sess.run(accuracy,
               feed_dict={x: mnisT.test.images, y_: mnisT.test.labels}))
