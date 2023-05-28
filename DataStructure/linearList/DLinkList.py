'''
    作者: btx
    日期: 23-5-27
    功能：双链表的基本实现
'''
class Node:
    def __init__(self, data=None):
        self.data = data
        self.prev = None
        self.next = None

class DLinkList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0 

    # 在链表尾插入元素
    def listAppend(self, data):
        node = Node(data)
        if not self.head:
            self.head = self.tail = node
        else:
            node.prev = self.tail
            self.tail.next = node
            self.tail = node
        self.size += 1
    
    # 在链表头插入元素
    def addFirst(self, data):
        node = Node(data)
        if not self.head:
            self.head = self.tail = node
        else:
            node.next = self.head
            self.head.prev = node
            self.head = node
        self.size += 1

    # 在指定位置插入 
    def listInsert(self, index, data):
        if index < 0 or index > self.size:
            return False
        # 头部插入
        elif index == 0:                   
            self.addFirst(data)
        elif index == self.size:
        # 尾部插入
            self.listAppend(data)
        else:
            new_node = Node(data)
            current = self.head
            for i in range(index - 1):
                current = current.next
            new_node.prev = current
            new_node.next = current.next
            current.next.prev = new_node
            current.next = new_node
            self.size += 1

    # 删除指定位置的元素
    def delete(self, index):
        if index < 0 or index >= self.size:
            return False
        elif index == 0:
            self.head = self.head.next
            if not self.head:
                self.tail = None
            else:
                self.head.prev = None
            self.size -= 1
        # 删除尾部结点
        elif index == self.size - 1:       
            self.tail = self.tail.prev
            self.tail.next = None
            self.size -= 1
        else:
            current = self.head
            for i in range(index):
                current = current.next
            current.prev.next = current.next
            current.next.prev = current.prev
            self.size -= 1

    # 获取指定位置的元素值
    def get(self, index):
        if index < 0 or index >= self.size: # 判断索引是否越界
            return False
        current = self.head
        for i in range(index):
            current = current.next
        return current.data

    # 更新指定位置的元素值
    def update(self, index, data):
        if index < 0 or index >= self.size:
            return False
        current = self.head
        for i in range(index):
            current = current.next
        current.data = data

    # 获取链表长度
    def getSize(self):
        return self.size

    # 判断链表是否为空
    def isEmpty(self):
        return self.size == 0
    
    #输出链表
    def printList(self):
        current = self.head
        res = '链表：'
        while current is not None:
            res += str(current.data)
            res += ' '
            current = current.next
        print(res)

    
if __name__ == '__main__' :
    L = DLinkList()
    # 插入数值
    print("插入数值")
    L.listAppend(1)
    L.listAppend(2)
    L.listAppend(3)
    L.printList()
    print("在第3个位置插入5")
    L.listInsert(2,5)
    L.printList()
    #查询
    print("查询第3个位置的元素")
    print(L.get(2))
    # 删除数值
    L.delete(1)
    print("删除第2个元素")
    L.printList()