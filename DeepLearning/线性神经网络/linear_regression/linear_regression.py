'''
梯度存储在 .grad

'''

# %matplotlib inline
import matplotlib.pyplot as plt
import random
import torch
from d2l import torch as d2l
'''
生成数据集
'''
def synthetic_data(w, b, num_examples):  #@save
    """生成y=Xw+b+噪声"""
    X = torch.normal(0, 1, (num_examples, len(w)))
    y = torch.matmul(X, w) + b
    y += torch.normal(0, 0.01, y.shape) #噪声  
    return X, y.reshape((-1, 1))

# 这里的w、b是自己设的
true_w = torch.tensor([2, -3.4])
true_b = 4.2
#生产特征值和标签
features, labels = synthetic_data(true_w, true_b, 1000)
# 注意，features中的每一行都包含一个二维数据样本， labels中的每一行都包含一维标签值（一个标量）。
print('features:', features[0],'\nlabel:', labels[0])
# 通过生成第二个特征features[:, 1]和labels的散点图， 可以直观观察到两者之间的线性关系。
d2l.set_figsize()
d2l.plt.scatter(features[:, 1].detach().numpy(), labels.detach().numpy(), 1);
'''
读取数据集
该函数接收批量大小、特征矩阵和标签向量作为输入，生成大小为batch_size的小批量。 每个小批量包含一组特征和标签。
'''
def data_iter(batch_size, features, labels):
    num_examples = len(features)
    indices = list(range(num_examples))
    # 这些样本是随机读取的，没有特定的顺序
    random.shuffle(indices)
    for i in range(0, num_examples, batch_size):
        batch_indices = torch.tensor(
            indices[i: min(i + batch_size, num_examples)])
        yield features[batch_indices], labels[batch_indices]
        
batch_size = 10

for X, y in data_iter(batch_size, features, labels):
    print(X, '\n', y)
    break

'''
初始化模型参数
在初始化参数之后，我们的任务是更新这些参数，直到这些参数足够拟合我们的数据。 
每次更新都需要计算损失函数关于模型参数的梯度。 有了这个梯度，我们就可以向减小损失的方向更新每个参数。
'''
w = torch.normal(0, 0.01, size=(2,1), requires_grad=True)
b = torch.zeros(1, requires_grad=True)
'''
定义模型
定义模型，将模型的输入和参数同模型的输出关联起来。 要计算线性模型的输出， 我们只需计算输入特征和模型权重的矩阵-向量乘法后加上偏置。 
（广播机制： 当我们用一个向量加一个标量时，标量会被加到向量的每个分量上。）
'''
def linreg(X, w, b):  #@save
    """线性回归模型"""
    return torch.matmul(X, w) + b  # torch.matmul是乘法运算
'''
定义损失函数（均方损失）
因为需要计算损失函数的梯度，所以我们应该先定义损失函数。 这里我们使用 3.1节中描述的平方损失函数。 
在实现中，我们需要将真实值y的形状转换为和预测值y_hat的形状相同。
'''
def squared_loss(y_hat, y):  #@save
    return (y_hat - y.reshape(y_hat.shape)) ** 2 / 2
'''
定义优化算法
尽管线性回归有解析解，但本书中的其他模型却没有。 这里我们介绍小批量随机梯度下降。
在每一步中，使用从数据集中随机抽取的一个小批量，然后根据参数计算损失的梯度。 
接下来，朝着减少损失的方向更新我们的参数。
下面的函数实现小批量随机梯度下降更新。 
该函数接受模型参数集合、学习速率和批量大小作为输入。
每一步更新的大小由学习速率lr决定。 
因为我们计算的损失是一个批量样本的总和，所以我们用批量大小（batch_size） 来规范化步长，这样步长大小就不会取决于我们对批量大小的选择。

梯度下降（gradient descent）方法： 这种方法几乎可以优化所有深度学习模型。 它通过不断地在损失函数递减的方向上更新参数来降低误差。

'''
def sgd(params, lr, batch_size):  #@save
    """小批量随机梯度下降"""
    with torch.no_grad():
        for param in params:                              #param表示每一个参数，可能是w、b
            param -= lr * param.grad / batch_size         # 求反向梯度的均值（.grad查看梯度）
            param.grad.zero_()                            #“清除”x的梯度值，也就是重新赋值为0
            
            
'''
训练
概括一下，我们将执行以下循环：
初始化参数
重复以下训练，直到完成：1)计算梯度 2)更新参数
在每个迭代周期（epoch）中，我们使用data_iter函数遍历整个数据集， 并将训练数据集中所有样本都使用一次（假设样本数能够被批量大小整除）。 
这里的迭代周期个数num_epochs和学习率lr都是超参数，分别设为3和0.03。 设置超参数很棘手，需要通过反复试验进行调整。 
'''        
lr = 0.03              #学习率
num_epochs = 3         #迭代次数
net = linreg           #线性回归模型
loss = squared_loss    #损失函数

for epoch in range(num_epochs):
    for X, y in data_iter(batch_size, features, labels):
        l = loss(net(X, w, b), y)  # X和y的小批量损失，预测的y和真实的y做一次损失计算
        # 因为l形状是(batch_size,1)，而不是一个标量。l中的所有元素被加到一起，
        # 并以此计算关于[w,b]的梯度
        l.sum().backward()  #计算批量中每个样本的偏导数之和
        sgd([w, b], lr, batch_size)  # 使用参数的梯度更新参数  
    with torch.no_grad():
        train_l = loss(net(features, w, b), labels)
        print(f'epoch {epoch + 1}, loss {float(train_l.mean()):f}') #输出当前迭代的损失函数
        
# 因为我们使用的是自己合成的数据集，所以我们知道真正的参数是什么。 因此，我们可以通过比较真实参数和通过训练学到的参数来评估训练的成功程度。
# 事实上，真实参数和通过训练学到的参数确实非常接近。
print(f'w的估计误差: {true_w - w.reshape(true_w.shape)}')
print(f'b的估计误差: {true_b - b}')