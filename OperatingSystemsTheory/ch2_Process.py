'''
    作者: btx
    日期: 23-6-1
    功能：进程(Process)
    笔记：
        -多任务的表现形式
            ·并发：在一段时间内交替执行多个任务 （单核CPU只能并发执行）
           · 并行：在一段时间内同时一起执行多个任务（需要多核CPU）
        -进程
            ·操作系统资源分配的最小单位，一个正在运行的程序就是一个进程
            ·程序运行会默认创建一个主进程
            ·程序运行后又创建的进程为子进程
            ·创建进程：
                通过进程类创建进程对象
                    进程对象 = multiprocessing.Process(target=任务名,args,kwargs)
                    任务名是一个函数名（方法名）
                启动进程执行任务
                    进程对象.start()
            ·进程执行带有参数的任务
                args 以元组方式传参
                    顺序必须一直参数一致
                    如果只有一个参数，写为args = (3,)
                kwargs 以字典形式传承，键值必须和参数名相同
            ·进程编号
                获取进程标识符(pid)
                    使用os模块实现
                    os.getpid() 获取当前进程标号
                    os.getppid() 获取父进程标号
            ·进程间不共享全局变量
                创建子进程的实质是拷贝了主进程的资源，主进程和子进程之间是独立的
            ·子进程和主进程的结束顺序
                主进程需要等待所有子进程结束再结束
                设置守护主进程
                    进程对象.daemon = True
                    主进程退出后子进程自动销毁
                销毁子进程
                    进程对象.terminate()
                    手动结束子进程

'''
import multiprocessing#多进程
import time
import os#用于获取进程标号
# 任务1
def task_1():
    print(">>>task1的pid:%d" % os.getpid(),end=" ")
    print("父进程pid:%d" % os.getppid())
    while 1:
        print("task_1")
        time.sleep(0.2)
# 任务2
def task_2(num):
    print(">>>task1的pid:%d" % os.getpid(),end=" ")
    print("父进程pid:%d" % os.getppid())
    for i in range(num):
        print("task_2")
        time.sleep(0.2)
# 任务3
def task_3(num):
    print(">>>task2的pid:%d" % os.getpid(),end=" ")
    print("父进程pid:%d" % os.getppid())
    for i in range(num):
        print("task_3")
        time.sleep(0.2)
if __name__ == '__main__':
    print(">>>主进程的pid>>>%d" % os.getpid())
    #创建进程对象
    process_1 = multiprocessing.Process(target=task_1)
    # process_1.daemon = True #守护子进程
    process_2 = multiprocessing.Process(target=task_2,kwargs={"num":2})
    process_3 = multiprocessing.Process(target=task_3,args=(5,))
    #启动进程
    process_1.start()
    process_2.start()
    process_3.start()
    #主进程结束
    time.sleep(2)
    # 手动销毁子进程
    process_1.terminate()
    print("主进程结束")