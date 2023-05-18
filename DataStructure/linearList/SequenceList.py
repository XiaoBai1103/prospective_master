'''
    作者: btx
    日期: 23-5-18
    功能：顺序表的基本实现
'''
class SeqList:  
    #初始化中设置顺序表长度
    def __init__(self, size):  
        self.lenth = 0 #当前长度
        self.size = size  #最大长度
        self.data = [None] * size  
    #状态判断
    def isFull(self):  
        return self.lenth == self.size
    #增加长度  
    def increase(self,len):
        self.size=len
    #向顺序表末尾添加一个元素
    def append(self, e):  
        if self.isFull():  
            return False
        else:
            self.data[self.lenth] = e  
            self.lenth += 1  
            return True
    #插入数据 位置:i 元素:e
    def insert(self, i, e):  
        if i < 0 or i > self.lenth or self.isFull():  
            return False
        else:
            #数据后移
            for j in range(self.lenth, i, -1):  
                self.data[j] = self.data[j-1]  
            self.data[i] = e
            self.lenth += 1
            return True  
    #删除数据 位置:i 元素:e
    def delete(self, i):  
        if i < 0 or i >= self.lenth:  
            return False
        else:  
            e = self.data[i] 
            for j in range(i, self.lenth-1):  
                self.data[j] = self.data[j+1]  
            self.data[self.lenth-1] = None  
            self.lenth -= 1 
            return e 

if __name__ == '__main__' :
    seq = SeqList(5)
    seq.append(1)
    seq.append(2)
    print(seq.data)
    seq.insert(1, 3)
    print(seq.data)
    seq.delete(0)
    print(seq.data)

    
