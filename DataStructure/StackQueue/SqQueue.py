'''
    作者: btx
    日期: 23-6-1
    功能：循环队列的基本实现
'''
class Queue:
    def __init__(self, capacity):
        self.capacity = capacity  # 队列容量
        self.front = 0  # 队首指针
        self.rear = 0  # 队尾指针
        self.queue = [None] * capacity  # 存储队列元素的数组
    #入队
    def enqueue(self, e):
        # 队列已满
        if (self.rear + 1) % self.capacity == self.front:
            print("队列已满")
            return False
        else:
            self.queue[self.rear] = e
            self.rear = (self.rear + 1) % self.capacity
            return True
    #出队
    def dequeue(self):
        # 队列为空
        if self.isEmpty():
            return None
        else:
            e = self.queue[self.front]
            self.front = (self.front + 1) % self.capacity
            return e

    def printQueue(self):
        if self.isEmpty():
            return None
        else:
            print("队列: ", end="")
            i = self.front
            while i != self.rear:
                print(self.queue[i], end=" ")
                i = (i + 1) % self.capacity
            print("")
    #判空
    def isEmpty(self):
        if self.front == self.rear:
            print("队列为空")
            return True
        else:
            return False
if __name__ == '__main__':
    queue = Queue(5)
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