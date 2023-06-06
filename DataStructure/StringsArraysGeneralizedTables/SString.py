class SeqString:
    def __init__(self, initStr=None):
        if initStr:
            self.data = list(initStr)
        else:
            self.data = []
    #返回串的字符串表示形式
    def __str__(self):
        return ''.join(self.data)
    #返回串的长度
    def __len__(self):
        return len(self.data)
    #实现序列访问操作
    def __getitem__(self, index):
        if isinstance(index, slice):
            start, stop, step = index.indices(len(self))
            return SeqString(''.join(self.data[start:stop:step]))
        else:
            if index < 0 or index >= len(self):
                raise IndexError('SeqString index out of range')
            return self.data[index]
    #实现序列赋值操作
    def __setitem__(self, index, value):
        if index < 0 or index >= len(self):
            raise IndexError('SeqString index out of range')
        self.data[index] = value
    #判断两个串是否相等
    def __eq__(self, other):
        if len(self) != len(other):
            return False
        for i in range(len(self)):
            if self[i] != other[i]:
                return False
        return True
    #拼串
    def __add__(self, other):
        new_data = self.data + other.data
        return SeqString(''.join(new_data))
    #实现串的重复操作
    def __mul__(self, n):
        new_data = self.data * n
        return SeqString(''.join(new_data))

'''
    模式匹配算法
        确定主串中所包含的子串(模式串)第一次出现的位置
        算法分类:BF算法、KMP算法
        BF算法：类似于滑动窗口的方法
'''
def bfMatch(mainStr, patternStr):
    m = len(patternStr)#模式串
    n = len(mainStr) #主串
    for i in range(n - m + 1):
        j = 0
        #相等则继续比较
        while j < m and mainStr[i+j] == patternStr[j]:
            j += 1
        #匹配成功
        if j == m:
            return i

    return -1


if __name__ == "__main__":
    s1 = SeqString('hello')
    print(s1)
    print(len(s1))  # 输出 5
    print(s1[0])  # 输出 h
    print(s1[1:4])  # 输出 ell
    s1[1] = 'a'
    print(s1)  # 输出 hallo
    s2 = SeqString('world')
    print(s1 == s2)  # 输出 False
    s3 = s1 + s2
    print(s3)  # 输出 halloworld
    s4 = s1 * 3
    print(s4)  # 输出 hallohallohallo
    print("模板匹配")
    print(bfMatch(s3,s2))

