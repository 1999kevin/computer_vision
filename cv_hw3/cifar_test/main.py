import torch
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision import transforms
from lenet import lenet5
from torch import nn

cifar_train = datasets.CIFAR10('./data',True,transform=transforms.Compose((  #true表示加载的是训练集
                                transforms.Resize(32,32),
                                transforms.ToTensor())))

cifar_train_batch = DataLoader(cifar_train,batch_size = 30,shuffle = True)

cifar_test = datasets.CIFAR10('./data',False,transform=transforms.Compose((  #false表示加载的是测试集
                                transforms.Resize(32,32),
                                transforms.ToTensor())))

cifar_test_batch = DataLoader(cifar_test,batch_size = 30,shuffle = True)


device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
net = lenet5()
net = net.to(device) #将网络部署到GPU上
loss_fn = nn.CrossEntropyLoss().to(device)
optimizer = torch.optim.Adam(net.parameters(),lr=1e-3)

# 开始训练
for epoch in range(10):
    for batchidx, (x, label) in enumerate(cifar_train_batch):
        x, label = x.to(device), label.to(device)  # x.size (bcs,3,32,32) label.size (bcs)
        logits = net.forward(x)
        loss = loss_fn(logits, label)  # logits.size:bcs*10,label.size:bcs

        # 开始反向传播：
        optimizer.zero_grad()
        loss.backward()  # 计算gradient
        optimizer.step()  # 更新参数
        if (batchidx + 1) % 400 == 0:
            print('这是本次迭代的第{}个batch'.format(batchidx + 1))  # 本例中一共有50000张照片，每个batch有30张照片，所以一个epoch有1667个batch

    print('这是第{}迭代，loss是{}'.format(epoch + 1, loss.item()))



# 测试
net.eval()
with torch.no_grad():
    correct_num = 0  # 预测正确的个数
    total_num = 0  # 测试集中总的照片张数
    batch_num = 0  # 第几个batch
    for batchidx, (x, label) in enumerate(cifar_test_batch):  # x的size是30*3*32*32（30是batch_size,3是通道数），label的size是30.
        # cifar_test中一共有10000张照片，所以一共有334个batch，因此要循环334次
        x, label = x.to(device), label.to(device)
        logits = net.forward(x)
        pred = logits.argmax(dim=1)
        correct_num += torch.eq(pred, label).float().sum().item()
        total_num += x.size(0)
        batch_num += 1
        if batch_num % 50 == 0:
            print('这是第{}个batch'.format(batch_num))  # 一共有10000/30≈334个batch

    acc = correct_num / total_num  # 最终的total_num是10000
    print('测试集上的准确率为：', acc)