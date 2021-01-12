import struct
from array import array
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image

with open("./data/MNIST/raw/train-images-idx3-ubyte", "rb") as f:
    magic, size, rows, cols = struct.unpack(">IIII", f.read(16))
    print(magic, size, rows, cols)
    image_data = array("B", f.read())
    images = []
    for i in range(size):
        images.append([0] * rows * cols)
    for i in range(size):
        images[i][:] = image_data[i * rows * cols:(i + 1) * rows * cols]


for i,img in enumerate(images):
    if i < 72:
        plt.subplot(9,8,i+1)
        img = np.array(img)
        img = img.reshape(rows,cols)
        img = Image.fromarray(img)
        plt.imshow(img, cmap='gray')
        plt.axis("off")
        # plt.show()
    else:
        # print("break")
        break

plt.show()

# import struct
# from array import array
with open("./data/MNIST/raw/train-labels-idx1-ubyte", "rb") as f:
    magic, size = struct.unpack(">II", f.read(8))
    labels = array("B", f.read())
    print(magic, size, labels)