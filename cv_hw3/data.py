import struct
from array import array
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image


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

# 打开一个空的新数据集
fo = open("./data/MNIST/raw/new-train-images-idx3-ubyte", "wb")


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


# 对原数据进行更改, 这里把0和1合并放在原来的1
# images[0][:] = images[1][:]
new_images = images.copy()
new_images[0][:] = combine(images[0], images[1], rows, cols)[:]
new_images[4][:] = flip(images[4], rows, cols)[:]



# 写入新数据集
for i in range(size):
    fo.write(bytes(new_images[i]))
fo.close()


# 读入新数据集
with open("./data/MNIST/raw/new-train-images-idx3-ubyte", "rb") as f:
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


