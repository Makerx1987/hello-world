import os
import cv2
import tensorflow as tf
from tensorflow.



imgpath='./tr-vf/'
imgnames=os.listdir(imgpath)
# print(imgnames[0:10])
# for i in range(0,len(imgnames)):
img=cv2.imread(imgpath+imgnames[0])
height=img.shape[0]
width=img.shape[1]
depth=img.shape[2]
print(height,width,depth)

Input=tf.keras.Input(shape=(height,width.depth),name="vfp")
cov1=layers.


