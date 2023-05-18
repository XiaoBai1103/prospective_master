'''
    作者: btx
    日期: 23-5-18
    功能：单链表的基本实现
'''
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None
    
    #在表尾插入    
    def listAppend(self, e):
        # 创建新节点
        node = Node(e)
        # 如果链表为空，则设置头节点为新节点
        if self.head is None:
            self.head = node
        else:
            # 遍历找到链表的尾部
            current = self.head
            while current.next is not None:
                current = current.next
            current.next = node
    
    # 在指定位置插入 前一个结点prevNode 元素:e
    def listInsert(self, prevNode, e):
        if prevNode is None:
            return False
        else:
            new_node = Node(e)
            current = self.head
            while current.next is not None and current.next.data != prevNode:
                current = current.next
            new_node.next = current.next.next
            current.next.next = new_node
            return True
    
    #删除节点
    def delete(self, data):
        if self.head is None:
            return False
        if self.head.data == data:
            # 如果要删除的节点是头节点，则将头节点指向下一个节点
            self.head = self.head.next
        else:
            current = self.head
            while current.next is not None and current.next.data != data:
                current = current.next
            if current.next is not None:
                # 找到要删除的节点并删除
                current.next = current.next.next
                
    def printList(self):
        current = self.head
        while current is not None:
            print(current.data)
            current = current.next

if __name__ == '__main__':
    # 初始化链表
    L = LinkedList()
    
    # 插入数值
    L.listAppend(1)
    L.listAppend(2)
    L.listAppend(3)
    L.listInsert(2,5)
    print("链表:")
    L.printList()
    
    # 删除数值
    L.delete(2)
    print("删除2后的链表:")
    L.printList()