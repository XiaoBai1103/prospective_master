'''
    作者: btx
    日期: 23-5-31
    功能：链栈的基本实现
'''
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Stack:
    def __init__(self):
        self.top = None
    #入栈
    def push(self, item):
        new_node = Node(item)
        new_node.next = self.top
        self.top = new_node
    #出栈
    def pop(self):
        if not self.is_empty():
            popped_node = self.top
            self.top = self.top.next
            popped_node.next = None
            return popped_node.data
    #获取栈顶元素
    def getTop(self):
        if not self.is_empty():
            return self.top.data

    def is_empty(self):
        return self.top is None

    def size(self):
        count = 0
        current = self.top
        while current:
            count += 1
            current = current.next
        return count
if __name__ == "__main__":
    stack = Stack()
    stack.push(1)
    stack.push(2)
    stack.push(3)
    print("输出当前栈的大小")
    print(stack.size())
    print("获取栈顶元素")
    print(stack.getTop())
    print("依次出栈")
    print(stack.pop())
    print(stack.pop())
    print(stack.pop())
    print(stack.pop())
    