# Train CIFAR10 with PyTorch

## program control parameters:<br>
--resume: training from checkpoint <br>
--test: test for checkpoint, now it can test lenet5 and resnet18 <br>
--net: choose network, now it supports 'lenet5', 'resnet18', 'mobileNetv' <br>
--epoch: indicate how many epochs you want to train<br>


## Test Only mode:
`python main.py --test --net=lenet5` <br>
`python main.py --test --net=resnet18`

**You should add data directory by yourself**



