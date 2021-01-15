from torch import nn
import torch
from torchsummary import summary


class lenet5(nn.Module):
    def __init__(self):
        super(lenet5, self).__init__()

        # 两层卷积
        self.conv_unit = nn.Sequential(
            nn.Conv2d(in_channels=3, out_channels=6, kernel_size=5, stride=1, padding=0),
            nn.AvgPool2d(kernel_size=2, stride=2, padding=0),
            nn.Conv2d(in_channels=6, out_channels=16, kernel_size=5, stride=1, padding=0),
            nn.AvgPool2d(kernel_size=2, stride=2, padding=0)
        )

        '''
        卷积之后先flatten,然后再全连接，但是nn.Module中没有flatten的操作，
        所以flatten不能包含在sequential中
        因此先用一个sequential完成卷积操作，然后flatten，然后再用一个sequential完成全连接
        '''

        # 全连接层
        self.fc_unit = nn.Sequential(
            nn.Linear(16 * 5 * 5, 120),
            nn.ReLU(),
            nn.Linear(120, 84),
            nn.ReLU(),
            nn.Linear(84, 11)
        )

    def forward(self, x):
        batch_size = x.shape[0]
        x = self.conv_unit(x)
        x = x.reshape(batch_size, 16 * 5 * 5)
        logits = self.fc_unit(x)
        return logits


if __name__ == '__main__':
    device = torch.device("cuda:6" if torch.cuda.is_available() else "cpu")  # PyTorch v0.4.0
    model = lenet5().to(device)
    summary(model, (3,32,32))