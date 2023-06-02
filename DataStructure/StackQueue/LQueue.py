'''
    作者: btx
    日期: 23-6-1
    功能：栈队的基本实现
'''
class Node:
    def __init__(self, data=None, next=None):
        self.data = data
        self.next = next

class Queue:
    def __init__(self):
        self.front = None
        self.rear = None
    #入队
    def enqueue(self, e):
        newNode = Node(e)
        if self.isEmpty():
            self.front = newNode
            self.rear = newNode
        else:
            self.rear.next = newNode
            self.rear = newNode
    #出队
    def dequeue(self):
        if self.isEmpty():
            return None
        else:
            e = self.front.data
            self.front = self.front.next
            if self.front == None:
                self.rear = None
            return e
    def printQueue(self):
        if self.isEmpty():
            print("队列为空")
            return None
        else:
            cur = self.front
            while cur:
                print(cur.data, end=' ')
                cur = cur.next
            print()
    def isEmpty(self):
        return self.front == None

if __name__ == '__main__':
    queue = Queue()
    queue.enqueue(1)
    queue.enqueue(2)
    queue.enqueue(3)
    queue.printQueue()
    print("出队：",end='')
    print(queue.dequeue())
    queue.printQueue()
    queue.enqueue(4)
    queue.enqueue(5)
    queue.enqueue(6)
    queue.printQueue()