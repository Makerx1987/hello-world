import numpy as np
import struct
import matplotlib.pyplot as plt

# 文件结构
# [offset] [type]          [value]          [description]
# 0000     32 bit integer  0x00000803(2051) magic number # 用于确认文件没有损坏
# 0004     32 bit integer  60000            number of images
# 0008     32 bit integer  28               number of rows
# 0012     32 bit integer  28               number of columns
# 0016     unsigned byte   ??               pixel
# 0017     unsigned byte   ??               pixel
# ........
# xxxx     unsigned byte   ??               pixel
# 1 rb	以二进制格式打开一个文件用于只读。文件指针将会放在文件的开头。这是默认模式。
# 2 创建文件体对象
# 3 创建文件数据对象
# 更简单写法 with open('train-images.idx3-ubyte','rb') as buf:
filename = 'train-images.idx3-ubyte'
binfile = open(filename, 'rb')
buf = binfile.read()

# '>IIII'是说使用大端法读取4个unsinged int32
# '>784B'的意思就是用大端法读取784个unsigned byte
# struct.calcsize():用来计算特定格式的输出的大小，是几个字节
# index索引很重要，相当于读取头、文件指针
# magic, numImages, numRows, numColumns = struct.unpack_from('>IIII', buf, 0)这一步用来说明属性，可有可无
index = 0
index += struct.calcsize('>IIII')
for i in range(100):

    im = struct.unpack_from('>784B', buf, index)
    index += struct.calcsize('>784B')

    im = np.array(im)
    im = im.reshape(28, 28)

    # 创建图
    # 创建子图
    # 灰度填充
    # 显示效果【关闭对话框可以显示下一条】
    fig = plt.figure()
    plotwindow = fig.add_subplot(111)
    plt.imshow(im, cmap='gray')
    plt.show()
