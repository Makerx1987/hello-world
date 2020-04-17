# tensorflow core
import tensorflow as tf
# a=3,b=5,(a+b)+(a*b)=?
node1 = tf.constant(3.0)
node2 = tf.constant(4.0)
print("node1:", node1, "\nnode2:", node2)
sess = tf.Session()
print("sess.run([node1,node2]):", sess.run([node1, node2]))
node3 = tf.add(node1, node2)
print("node3:", node3)
print("sess.run(node3):", sess.run(node3))
a = tf.placeholder(tf.float32)
b = tf.placeholder(tf.float32)
adder_node = a + b
print("sess.run(adder_node,{a:3,b:4.5}):",
      sess.run(adder_node, {a: 3, b: 4.5}))
print("sess.run(adder_node,{a:[1,3],b:[2,4]}):",
      sess.run(adder_node, {a: [1, 3], b: [2, 4]}))
adderandtriple = adder_node * 3
print("sess.run(adderandtriple,{a:3,b:4.5}):",
      sess.run(adderandtriple, {a: 3, b: 4.5}))
W = tf.Variable([.3], dtype=tf.float32)
b = tf.Variable([-.3], dtype=tf.float32)
x = tf.placeholder(dtype=tf.float32)
linearmodel = tf.matmul(x, W) + b
initv = tf.global_variables_initializer()
sess.run(initv)
print("sess.run(linearmodel,{x:[1,2,3,4]}):",
      sess.run(linearmodel, {x: [1, 2, 3, 4]}))
y = tf.placeholder(tf.float32)
squareddeltas = tf.square(linearmodel - y)
loss = tf.reduce_mean(squareddeltas)
print("sess.run(loss,{x:[1,2,3,4],y:[0,-1,-2,-3]}):",
      sess.run(loss, {x: [1, 2, 3, 4], y: [0, -1, -2, -3]}))
fixW = tf.assign(W, [-1.])
fixb = tf.assign(b, [1.])
sess.run([fixW, fixb])
print("sess.run(loss,{x:[1,2,3,4],y:[0,-1,-2,-3]}):",
      sess.run(loss, {x: [1, 2, 3, 4], y: [0, -1, -2, -3]}))
opti = tf.train.GradientDescentOptimizer(0.01)
train = opti.minimize(loss)
for i in range(1000):
    sess.run(train, {x: [1, 2, 3, 4], y: [0, -1, -2, -3]})
print("sess.run([W,b]):", sess.run([W, b]))
