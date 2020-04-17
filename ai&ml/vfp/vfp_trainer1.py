import os
import cv2
import tensorflow as tf
from tensorflow.keras import layers



imgpath='./tr-vf/'
imgnames=os.listdir(imgpath)
for i in range(0,len(imgnames)):
    img=cv2.imread(imgpath+imgnames[i])
    height=img.shape[0]
    width=img.shape[1]
    depth=img.shape[2]
    print(imgnames[i],height,width,depth)
    if i>20 :
        break


# inputs=tf.keras.Input(shape=(height,width,depth),name="vfp")
# cov1=layers.Conv2D(8,(10,10),padding='same',activation='relu')(Input)
# max1=layers.MaxPool2D(2)(cov1)
# cov2=layers.Conv2D(4,(5,5),padding='same',activation='relu')(max1)
# max2=layers.MaxPool2D(5)(cov2)
# cov3=layers.Conv2D(2,(3,3),padding='same',activation='relu')(max2)
# max3=layers.MaxPool2D((8,5),strides=4,padding='valid')(cov3)
# resh=max3.reshape(4,192)
# drop=resh.dropout(0.9)
# outputs=layers.Dense(192,36,activation='softmax')(resh)
# model = tf.keras.Model(inputs=inputs, outputs=outputs, name='VGG16+')

# model.compile(optimizer=tf.keras.optimizers.RMSprop(),
#              loss='sparse_categorical_crossentropy', # 直接填api，后面会报错
#              metrics=['accuracy'])

# history = model.fit(x_train, y_train, batch_size=64, epochs=5, validation_split=0.2)
# test_scores = model.evaluate(x_test, y_test, verbose=0)
# print('test loss:', test_scores[0])
# print('test acc:', test_scores[1])

