# https://pytorch.org/docs/stable

import numpy as np
import torch
from torch import nn
from torch.utils import data
from d2l import torch as d2l
true_w = torch.tensor([2, -3.4])
true_b = 4.2
'''
⽣成数据集
'''
features, labels = d2l.synthetic_data(true_w, true_b, 1000)
'''
读取数据集
    
'''
def load_array(data_arrays, batch_size, is_train=True): #@save
    """构造⼀个PyTorch数据迭代器"""
    #torch.utils.data.TensorDataset方法，数据集包装张量。
    # Dataset wrapping tensors.
    # Each sample will be retrieved by indexing tensors along the first dimension.
    dataset = data.TensorDataset(*data_arrays) 
    #dataloader就能够帮助我们包装数据，还能够有效的进行数据迭代，以达到批训练的目的。
    #batch_size：接收批量大小 shuffle
    return data.DataLoader(dataset, batch_size, shuffle=is_train)

batch_size = 10                                              #接收批量大小
data_iter = load_array((features, labels), batch_size)       
'''
例：
next()函数用于取出可迭代对象的元素，一般与iter()函数联合使用。
iter() 函数用来生成迭代器。
    list = ['a', 'b', 'c']
    elm = iter(list)
    print(next(elm))  #a
    print(next(elm))  #b
    print(next(elm))  #c
'''
next(iter(data_iter))

'''
定义模型
nn.Linear定义一个神经网络的线性层
torch.nn.Linear(in_features, # 输入的神经元个数
           out_features, # 输出神经元个数
           bias=True # 是否包含偏置
           )

Sequential 是一个容器 
net[0]实际就是nn.Linear(2, 1)
'''
net = nn.Sequential(nn.Linear(2, 1)) # 输入特征数为2，输出特征数为1
'''
定义参数
'''
net[0].weight.data.normal_(0, 0.01)  #使用正态分布替换data值
net[0].bias.data.fill_(0)  #偏置b设置为0
'''
定义损失函数
（均方误差） 参数：(input, target)
'''
loss = nn.MSELoss()
'''
定义优化算法
（随梯度下降）
'''
trainer = torch.optim.SGD(net.parameters(), lr=0.03)

'''
训练

'''
num_epochs = 3   #迭代次数
for epoch in range(num_epochs):
    for X, y in data_iter:
        l = loss(net(X) ,y)
        trainer.zero_grad()  #梯度清零
        l.backward()  #此处pyTorch已经做了sum，所以直接backward即可
        trainer.step()  #模型更新
    l = loss(net(features), labels)
    print(f'epoch {epoch + 1}, loss {l:f}')

'''
比较
'''
w = net[0].weight.data
print('w的估计误差：', true_w - w.reshape(true_w.shape))
b = net[0].bias.data
print('b的估计误差：', true_b - b)
