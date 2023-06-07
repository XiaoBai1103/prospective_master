'''
    作者：btx
    日期：23-6-6
    功能：串的顺序存储
'''
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
    if m == 0:
        return [i for i in range(n)]
    # 进行匹配
    for i in range(n - m + 1):
        j = 0
        #相等则继续比较
        while j < m and mainStr[i+j] == patternStr[j]:
            j += 1
        #匹配成功返回i，不成功则回溯继续匹配
        if j == m:
            return i

    return -1
'''
    KMP算法
        利用已经部分匹配的结果加速模式串的滑动速度
        定义next[j]函数，表明当模式中的第j个字符与主串中相应字符“失配”时，在模式中需重新和主串中该字符进行比较字符的位置

'''
def KMP_Match(mainStr, patternStr):
    m = len(patternStr)#模式串
    n = len(mainStr) #主串
    if m == 0:
        return [i for i in range(n)]
    # 计算 next 数组
    next = [0] * m
    j = 0
    for i in range(1, m):
        while j > 0 and patternStr[j] != patternStr[i]:
            j = next[j - 1]
        if patternStr[j] == patternStr[i]:
            j += 1
        next[i] = j
    # 进行匹配
    res = []
    j = 0
    for i in range(n):
        while j > 0 and mainStr[i] != patternStr[j]:
            #根据next数组进行回溯
            j = next[j - 1]
        if mainStr[i] == patternStr[j]:
            j += 1
        if j == m:
            res.append(i - m + 1)
            #根据next数组进行回溯
            j = next[j - 1]
    return res

if __name__ == "__main__":
    s1 = SeqString('hello')
    print(s1)
    print(len(s1))
    print(s1[0])
    print(s1[1:4])
    s1[1] = 'a'
    print(s1)
    s2 = SeqString('world')
    s = SeqString('wor')
    print(s1 == s2)
    s3 = s1 + s + s2
    print(s3)
    s4 = s1 * 3
    print(s4)
    print("模板匹配 BF算法",end='')
    print(bfMatch(s3,s2))
    print("模板匹配 KMP算法",end='')
    print(KMP_Match(s3,s2))
