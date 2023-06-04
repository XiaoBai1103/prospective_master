# %matplotlib inline
import torch
import torchvision
import matplotlib.pyplot as plt
from torch.utils import data
from torchvision import transforms
from d2l import torch as d2l
d2l.use_svg_display()
# 通过ToTensor实例将图像数据从PIL类型变换成32位浮点数格式，
# 并除以255使得所有像素的数值均在0〜1之间
trans = transforms.ToTensor()  #转换成Tensor
#训练集
mnist_train = torchvision.datasets.FashionMNIST(root="./data", train=True, transform=trans, download=True)
#测试集
mnist_test = torchvision.datasets.FashionMNIST(root="./data", train=False, transform=trans, download=True)
#查看训练集、测试集的大小
print(len(mnist_train), len(mnist_test))
#查看第一张图片（数据集由灰度图像组成，其通道数为1，⾼度和宽度均为28像素）
print(mnist_train[0][0].shape)

'''
    函数用于在数字标签索引及其文本名称之间进行转换
'''
def get_fashion_mnist_labels(labels): #@save
    """返回Fashion-MNIST数据集的⽂本标签"""
    text_labels = ['t-shirt', 'trouser', 'pullover', 'dress', 'coat',
    'sandal', 'shirt', 'sneaker', 'bag', 'ankle boot']
    return [text_labels[int(i)] for i in labels]
'''
    样本可视化
'''
def show_images(imgs, num_rows, num_cols, titles=None, scale=1.5):  #@save
    """绘制图像列表"""
    figsize = (num_cols * scale, num_rows * scale)
    _, axes = d2l.plt.subplots(num_rows, num_cols, figsize=figsize)
    axes = axes.flatten()
    for i, (ax, img) in enumerate(zip(axes, imgs)):
        if torch.is_tensor(img):
            # 图片张量
            ax.imshow(img.numpy())
            
        else:
            # PIL图片
            ax.imshow(img)
           
        ax.axes.get_xaxis().set_visible(False)
        ax.axes.get_yaxis().set_visible(False)
        if titles:
            ax.set_title(titles[i])
    return axes

X, y = next(iter(data.DataLoader(mnist_train, batch_size=18)))
#查看训练数据集中前几个样本的图像及其相应的标签
show_images(X.reshape(18, 28, 28), 2, 9, titles=get_fashion_mnist_labels(y));
plt.show()
'''
    读取小批量
'''
batch_size = 256

def get_dataloader_workers():  #@save
    """使用8个进程来读取数据"""
    return 8

train_iter = data.DataLoader(mnist_train, batch_size, shuffle=True,
                             num_workers=get_dataloader_workers())
#查看读取时间
timer = d2l.Timer()
for X, y in train_iter:
    continue
print(timer.stop())