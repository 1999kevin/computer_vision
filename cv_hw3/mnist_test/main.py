# -*-coding:utf-8-*-
import torch
import torch.nn as nn
import torchvision
import torchvision.transforms as transforms
import os
import numpy as np
from array import array
from torch.utils.data import Dataset
# from torch.utils.data import DataLoader


device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')

num_epochs = 5
num_classes = 10
batch_size = 100
learning_rate = 0.001


class Mnist(Dataset):
    def __init__(self, root, train=True, transform=None):

        # 根据是否为训练集，得到文件名前缀
        self.file_pre = 'train' if train == True else 't10k'
        self.transform = transform

        # 生成对应数据集的图片和标签文件路径
        self.label_path = os.path.join(root,
                                       '%s-labels-idx1-ubyte' % self.file_pre)
        self.image_path = os.path.join(root,
                                       '%s-images-idx3-ubyte' % self.file_pre)

        # 读取文件数据，返回图片和标签
        self.images, self.labels = self.__read_data__(
            self.image_path,
            self.label_path,
            train)

    def __read_data__(self, image_path, label_path, train):
        # 数据集读取
        with open(label_path, 'rb') as lbpath:
            labels = np.frombuffer(lbpath.read(), np.uint8,
                                   offset=8)
        count = 60000 if train == True else 10000

        with open(image_path, "rb") as imgpath:
            image_data = array("B", imgpath.read())
            images = []
            for i in range(count):
                images.append([0] * 28 * 28)
            for i in range(count):
                images[i][:] = image_data[i * 28 * 28:(i + 1) * 28 * 28]
        images = np.array(images, dtype=np.float32).reshape(count, 28, 28)
        images /= 255
        '''
        with open(image_path, 'rb') as imgpath:
            images = np.frombuffer(imgpath.read(), np.uint8,
                                   offset=16).reshape(len(labels), 28, 28)
        '''
        return images, labels

    def __getitem__(self, index):
        image, label = self.images[index], int(self.labels[index])

        # 如果需要转成 tensor 则使用 tansform
        if self.transform is not None:
            image = self.transform(np.array(image))  # 此处需要用 np.array(image)
        return image, label

    def __len__(self):
        return len(self.labels)


# MNIST dataset
train_dataset = Mnist(root='data2/MNIST/raw',
                      train=True,
                      transform=transforms.ToTensor())

test_dataset = Mnist(root='data2/MNIST/raw',
                     train=False,
                     transform=transforms.ToTensor())

# Data loader
train_loader = torch.utils.data.DataLoader(dataset=train_dataset,
                                           batch_size=batch_size,
                                           shuffle=True)

test_loader = torch.utils.data.DataLoader(dataset=test_dataset,
                                          batch_size=batch_size,
                                          shuffle=False)


class LetNet5(nn.Module):
    def __init__(self, num_clases=10):
        super(LetNet5, self).__init__()

        self.c1 = nn.Sequential(
            nn.Conv2d(1, 6, kernel_size=5, stride=1, padding=2),
            nn.BatchNorm2d(6),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2)
        )

        self.c2 = nn.Sequential(
            nn.Conv2d(6, 16, kernel_size=5),
            nn.BatchNorm2d(16),
            nn.ReLU(),
            nn.MaxPool2d(kernel_size=2, stride=2)
        )

        self.c3 = nn.Sequential(
            nn.Conv2d(16, 120, kernel_size=5),
            nn.BatchNorm2d(120),
            nn.ReLU()
        )

        self.fc1 = nn.Sequential(
            nn.Linear(120, 84),
            nn.ReLU()
        )

        self.fc2 = nn.Sequential(
            nn.Linear(84, num_classes),
            nn.LogSoftmax()
        )

    def forward(self, x):
        out = self.c1(x)
        out = self.c2(out)
        out = self.c3(out)
        out = out.reshape(out.size(0), -1)
        out = self.fc1(out)
        out = self.fc2(out)
        return out


model = LetNet5(num_classes).to(device)

criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

total_step = len(train_loader)
for epoch in range(num_epochs):
    for i, (images, labels) in enumerate(train_loader):
        images = images.to(device)
        labels = labels.to(device)

        # Forward pass
        outputs = model(images)
        loss = criterion(outputs, labels)

        # Backward and optimize
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if (i + 1) % 100 == 0:
            print('Epoch [{}/{}], Step [{}/{}], Loss: {:.4f}'
                  .format(epoch + 1, num_epochs, i + 1, total_step, loss.item()))

# Test the model
model.eval()  # eval mode (batchnorm uses moving mean/variance instead of mini-batch mean/variance)
with torch.no_grad():
    correct = 0
    total = 0
    for images, labels in test_loader:
        images = images.to(device)
        labels = labels.to(device)
        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        total += labels.size(0)
        correct += (predicted == labels).sum().item()

    print('Test Accuracy of the model on the 10000 test images: {} %'.format(100 * correct / total))

torch.save(model.state_dict(), 'LetNet-5.ckpt')


