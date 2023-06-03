'''
    作者: btx
    日期: 23-6-2
    功能：线程(Thread)
    笔记：
        -线程的概念：
            线程上程序执行的最小单位，进程负责分配资源，利用资源执行程序的是线程，可以说进程是线程的容器。
            同一进程的线程共享进程所拥有的全部资源
        -多线程完成多任务
            导入threading
            线程对象 = threading.Thread(target=任务名,name,group)
                可省参数: name:线程名  group:线程组
            线程对象.start()
        -带参数的任务
            与进程相同
        -主线程与子线程的结束顺序
            主线程等待所有子线程执行完毕再结束
            设置守护主线程
                    线程对象.daemon = True 或 线程对象.setDaemon(True)
                    主进程退出后子进程自动销毁
            销毁子进程
                进程对象.terminate()
                手动结束子进程
        -获取进程信息
            线程对象.current_thread
        -线程间执行顺序
            线程执行顺序与创建顺序无关，其执行顺序是无序的，主要由CPU调度实现
        -全局变量共享
            同一进程内的线程共享全局变量
        -线程间资源竞争
            当其中一个线程获取全局变量的值并在处理的过程中，未将处理好的值返还，但另一个线程此时获取了全局变量，则会出现错误
            ·线程同步：保证同一时刻只有一个线程操作全局变量
        -互斥锁
            ·对共享数据进行锁定，保证同一时刻只有一个线程去操作
            *互斥锁是多个线程一起抢，先抢到的先执行，未抢到的等待锁释放再去抢
            ·代码实现
                创建锁 mutex = threading.Lock()
                上锁   mutex.acquire()
                释放锁 mutex.release()
        -死锁
            ·一直等待对方释放锁，造成应用程序停止响应
            编写程序时要及时释放锁


'''
import threading#多线程
import time
import os#用于获取进程、线程标号
#全局变量
count = 0
# 任务1
def task_1():
    getInfo('task1')
    while 1:
        print("task_1")
        time.sleep(0.2)
# 任务2
def task_2(num):
    getInfo('task2')
    #上锁
    mutex.acquire()
    for i in range(num):
        global count
        count += 1
    #解锁
    mutex.release()
    print("count=",count)
    
# 任务3
def task_3(num):
    getInfo('task3')
    #上锁
    mutex.acquire()
    for i in range(num):
        global count
        count += 1
    #解锁
    mutex.release()
    print("count=",count)
# 获取父进程、进程以及线程标号
def getInfo(name):
    print(name,end='>>>')
    print("父进程:%d" % os.getppid(),end=",")
    print("进程:%d" % os.getpid(),end=",")
    print("线程信息:",end='')
    print(threading.current_thread())


if __name__ == '__main__':
    #创建锁
    mutex = threading.Lock()
    getInfo('主进程')
    #创建线程对象
    thread_1 = threading.Thread(target=task_1)
    thread_1.daemon = True #守护子进程
    thread_2 = threading.Thread(target=task_2,kwargs={"num":10000})
    thread_3 = threading.Thread(target=task_3,args=(10000,))
    #启动线程
    thread_1.start()
    thread_2.start()
    thread_3.start()
    #主进程结束
    time.sleep(3)
    print("主线程结束")