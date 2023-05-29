'''
    作者: btx
    日期: 23-5-28
    功能：循环链表的基本实现
'''
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class CircularLinkedList:
    def __init__(self):
        self.head = None
    # 在链表尾插入元素
    def listAppend(self, e):
        new_node = Node(e)
        if self.head is None:
            self.head = new_node
            new_node.next = self.head
        else:
            current = self.head
            while current.next != self.head:
                current = current.next
            current.next = new_node
            new_node.next = self.head
    # 在指定位置插入 前一个结点prevNode 元素:e
    def listInsert(self, prevNode, e):
        new_node = Node(e)
        if not self.head:
            self.head = new_node
            new_node.next = self.head
        elif prevNode == 0:
            current = self.head
            while current.next != self.head:
                current = current.next
            current.next = new_node
            new_node.next = self.head
            self.head = new_node
        else:
            current = self.head
            for i in range(prevNode-1):
                current = current.next
            new_node.next = current.next
            current.next = new_node
     #删除节点
    def delete(self, e):
        if self.head is None:
            return False
        if self.head.data == e:
            current = self.head
            while current.next != self.head:
                current = current.next
            current.next = self.head.next
            self.head = self.head.next
        else:
            current = self.head
            prev = None
            while current.next != self.head:
                prev = current
                current = current.next
                if current.data == e:
                    prev.next = current.next
                    current = current.next
    #输出链表
    def printList(self):
        if self.head is None:
            print("空链表")
        else:
            res = '链表：'
            current = self.head
            res += str(current.data)
            res += ' '
            while current.next != self.head:
                current = current.next
                res += str(current.data)
                res += ' '
            print(res)

if __name__ == '__main__':
    L = CircularLinkedList()
    print("插入数值")
    L.listAppend(1)
    L.listAppend(2)
    L.listAppend(3)
    L.listAppend(4)
    L.printList() 
    print("在第三个位置插入5")
    L.listInsert(2,5)
    L.printList()
    print("删除2")
    L.delete(2)
    L.printList()

