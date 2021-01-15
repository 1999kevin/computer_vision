import torch
from torch.utils.data import DataLoader
from torchvision import datasets
from torchvision import transforms
import torch.optim as optim
from torch import nn
import os
from Cifar import *
import argparse
from models.lenet import lenet5
from models.mobilenetv2 import *
from models.resnet import *


parser = argparse.ArgumentParser(description='PyTorch CIFAR10 Training')
parser.add_argument('--lr', default=0.1, type=float, help='learning rate')
parser.add_argument('--resume', '-r', action='store_true',
                    help='resume from checkpoint')
parser.add_argument('--test', '-t', action='store_true',
                    help='test with checkpoint')
parser.add_argument('--net', '-n', default='lenet5',type=str,
                    help='choose network, choose from mobileNetV2, resnet18, lenet5')
parser.add_argument('--epoch', '-e', default=10,type=int,
                    help='how many epoch will train')

args = parser.parse_args()


device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
best_acc = 0  # best test accuracy
start_epoch = 0  # start from epoch 0 or last checkpoint epoch
if not args.test:
    training_epoch = args.epoch
else:
    training_epoch = 0

net_name = args.net
loading_path = './checkpoint/'+net_name+'-ckpt.pth'
saving_path = './checkpoint/'+net_name+'-ckpt.pth'




# get data from Cifar.py
print('==> Preparing data..')
trainset = cifar_train
trainloader = cifar_train_batch
testset = cifar_test
testloader = cifar_test_batch


classes = ('plane', 'car', 'bird', 'cat', 'deer',
           'dog', 'frog', 'horse', 'ship', 'truck')

# Model
print('==> Building model..')
print("net: ", net_name)

if net_name == 'mobileNetV2':
    net = MobileNetV2(11)
elif net_name == 'resnet18':
    net = ResNet18(11)
elif net_name == 'lenet5':
    net = lenet5()
else:
    print("error network name")
    exit(1)


print("total training epochs in this script:", training_epoch)
print("saving path: ", saving_path)

if device.type == 'cuda':
    net = net.to(device) #将网络部署到GPU上

if args.resume or args.test:
    # Load checkpoint.
    print('==> Resuming from checkpoint..')
    print("loading path: ", loading_path)
    assert os.path.isdir('checkpoint'), 'Error: no checkpoint directory found!'
    checkpoint = torch.load(loading_path)
    net.load_state_dict(checkpoint['net'])
    best_acc = checkpoint['acc']
    start_epoch = checkpoint['epoch']

if device.type == 'cuda':
    criterion = nn.CrossEntropyLoss().to(device)
else:
    criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(net.parameters(),lr=1e-3)
scheduler = torch.optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max=200)



# Training
def train(epoch):
    print('\nEpoch: %d' % epoch)
    net.train()
    train_loss = 0
    correct = 0
    total = 0
    for batch_idx, (inputs, targets) in enumerate(trainloader):
        if device.type == 'cuda':
            inputs, targets = inputs.to(device), targets.to(device)
        optimizer.zero_grad()
        outputs = net(inputs)
        loss = criterion(outputs, targets)
        loss.backward()
        optimizer.step()

        train_loss += loss.item()
        _, predicted = outputs.max(1)
        total += targets.size(0)
        correct += predicted.eq(targets).sum().item()

        # progress_bar(batch_idx, len(trainloader), 'Loss: %.3f | Acc: %.3f%% (%d/%d)'
        #              % (train_loss/(batch_idx+1), 100.*correct/total, correct, total))
    # print('Loss:',train_loss/(batch_idx+1),' Acc: ', 100.*correct/total, correct, '/', total)
    print('Training loss: %f, Acc: %f%% = %d / %d' %(train_loss/(batch_idx+1), 100.*correct/total, correct, total))



def test(epoch):
    global best_acc
    net.eval()
    test_loss = 0
    correct = 0
    total = 0
    with torch.no_grad():
        for batch_idx, (inputs, targets) in enumerate(testloader):
            if device.type == 'cuda':
                inputs, targets = inputs.to(device), targets.to(device)
            outputs = net(inputs)
            loss = criterion(outputs, targets)

            test_loss += loss.item()
            _, predicted = outputs.max(1)
            total += targets.size(0)
            correct += predicted.eq(targets).sum().item()
        print('Testing loss: %f, Acc: %f%% = %d / %d' % (test_loss / (batch_idx + 1), 100. * correct / total, correct, total))

    # Save checkpoint.
    acc = 100.*correct/total
    if acc > best_acc:
        print('Saving..')
        state = {
            'net': net.state_dict(),
            'acc': acc,
            'epoch': epoch,
        }
        if not os.path.isdir('checkpoint'):
            os.mkdir('checkpoint')
        torch.save(state, saving_path)
        best_acc = acc



if not args.test:
    for epoch in range(start_epoch, start_epoch+training_epoch):
        train(epoch)
        test(epoch)
        scheduler.step()
else:
    test(start_epoch)