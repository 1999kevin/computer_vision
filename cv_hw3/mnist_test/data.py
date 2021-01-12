import struct
from array import array
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


num0, num1 = 8,4  # 前者是label和主要数，后者是背景数


# 把images1上非黑的地方覆盖到image2上
def combine(image1, image2, rows, cols):
    new_image = image2.copy()
    for i in range(rows*cols):
        if image1[i] != 0:
            new_image[i] = image1[i]
    return new_image

def flip(image, rows, cols):
    new_image = image.copy()
    for i in range(rows):
        for j in range(cols):
            new_image[i*cols+j] = image[j*cols+i]
    return new_image

# 从labels[cur_index]找到下一个是num的index
def nextIndex(num, cur_index, max_index):
    index = cur_index+1
    flag = False
    if index >= max_index:
        index -= max_index
        flag = True
    while labels[index] != num:
        index+=1
        if index >= max_index:
            index -= max_index
            flag = True
    return index, flag

# 打开一个空的新数据集
fo = open("./data2/MNIST/raw/train-images-idx3-ubyte", "wb")


# 读入原数据集图片
with open("./data/MNIST/raw/train-images-idx3-ubyte", "rb") as f:
    a =  f.read(16)
    fo.write(a)     #写入前面一部分
    magic, size, rows, cols = struct.unpack(">IIII",a)
    a = f.read()
    image_data = array("B", a)
    images = []
    for i in range(size):
        images.append([0] * rows * cols)
    for i in range(size):
        images[i][:] = image_data[i * rows * cols:(i + 1) * rows * cols]


# 读入labels
with open("./data/MNIST/raw/train-labels-idx1-ubyte", "rb") as f:
    magic, size = struct.unpack(">II", f.read(8))
    labels = array("B", f.read())
    # print(magic, size, labels)


# 对原数据进行更改, 这里把1翻转作为背景，把0叠加在这个背景上，放在label为0的位置
new_images = images.copy()


index0, _ = nextIndex(num0,-1, size)
index1, _ = nextIndex(num1,-1, size)

while True:
    new_images[index0][:] = combine(images[index0], flip(images[index1], rows, cols), rows, cols)[:]
    index0, flag = nextIndex(num0, index0, size)
    index1, _ = nextIndex(num1, index1, size)
    if flag:
        break


# 写入新数据集
for i in range(size):
    fo.write(bytes(new_images[i]))
fo.close()


# 读入新数据集
with open("./data2/MNIST/raw/train-images-idx3-ubyte", "rb") as f:
    a =  f.read(16)
    magic, size, rows, cols = struct.unpack(">IIII",a)
    a = f.read()
    image_data = array("B", a)
    images = []
    for i in range(size):
        images.append([0] * rows * cols)
    for i in range(size):
        images[i][:] = image_data[i * rows * cols:(i + 1) * rows * cols]

fo.close()

# 展示前72张图片。查看更改效果
for i,img in enumerate(images):
    if i < 72:
        plt.subplot(9,8,i+1)
        img = np.array(img)
        img = img.reshape(rows,cols)
        img = Image.fromarray(img)
        plt.imshow(img, cmap='gray')
        plt.axis("off")
    else:
        break
plt.show()


# 再来一次转化testing set

# 打开一个空的新数据集
fo = open("./data2/MNIST/raw/t10k-images-idx3-ubyte", "wb")


# 读入原数据集图片
with open("./data/MNIST/raw/t10k-images-idx3-ubyte", "rb") as f:
    a =  f.read(16)
    fo.write(a)     #写入前面一部分
    magic, size, rows, cols = struct.unpack(">IIII",a)
    a = f.read()
    image_data = array("B", a)
    images = []
    for i in range(size):
        images.append([0] * rows * cols)
    for i in range(size):
        images[i][:] = image_data[i * rows * cols:(i + 1) * rows * cols]


# 读入labels
with open("./data/MNIST/raw/t10k-labels-idx1-ubyte", "rb") as f:
    magic, size = struct.unpack(">II", f.read(8))
    labels = array("B", f.read())
    # print(magic, size, labels)


# 对原数据进行更改, 这里把1翻转作为背景，把0叠加在这个背景上，放在label为0的位置
new_images = images.copy()

# num0, num1 = 0,1  # 前者是label和主要数，后者是背景数
index0, _ = nextIndex(num0,-1, size)
index1, _ = nextIndex(num1,-1, size)

while True:
    new_images[index0][:] = combine(images[index0], flip(images[index1], rows, cols), rows, cols)[:]
    index0, flag = nextIndex(num0, index0, size)
    index1, _ = nextIndex(num1, index1, size)
    if flag:
        break


# 写入新数据集
for i in range(size):
    fo.write(bytes(new_images[i]))
fo.close()


# 读入新数据集
with open("./data2/MNIST/raw/t10k-images-idx3-ubyte", "rb") as f:
    a =  f.read(16)
    magic, size, rows, cols = struct.unpack(">IIII",a)
    a = f.read()
    image_data = array("B", a)
    images = []
    for i in range(size):
        images.append([0] * rows * cols)
    for i in range(size):
        images[i][:] = image_data[i * rows * cols:(i + 1) * rows * cols]

fo.close()

# 展示前72张图片。查看更改效果
for i,img in enumerate(images):
    if i < 72:
        plt.subplot(9,8,i+1)
        img = np.array(img)
        img = img.reshape(rows,cols)
        img = Image.fromarray(img)
        plt.imshow(img, cmap='gray')
        plt.axis("off")
    else:
        break
plt.show()


