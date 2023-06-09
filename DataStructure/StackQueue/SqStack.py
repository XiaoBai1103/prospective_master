'''
    作者: btx
    日期: 23-5-31
    功能：顺序栈的基本实现
'''
class Stack:
    def __init__(self):
        self.stack = []
    #入栈
    def push(self, item):
        self.stack.append(item)
    #出栈
    def pop(self):
        if not self.is_empty():
            return self.stack.pop()
    #获取栈顶元素
    def getTop(self):
        if not self.is_empty():
            return self.stack[-1]

    def is_empty(self):
        return len(self.stack) == 0

    def size(self):
        return len(self.stack)
    
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
