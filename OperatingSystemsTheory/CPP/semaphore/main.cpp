/*
    作者：btx
    创建日期：23-6-30
    功能：信号量semaphore 
*/
#include <iostream>  
#include <thread>  
#include <semaphore>
using namespace std;

// semaphore的成员函数
// release 相当于condition_variable中的通知(notify)
// acquire 相当于condition_variable中的等待(wait)

// 条件信号量(二进制信号量） 初始值为0
// 当信号量的值为0时，表示资源已被占用或不可用，其他线程需要等待。
// 当信号量的值为1时，表示资源可用或空闲，其他线程可以获取或使用该资源。
binary_semaphore bsem(0);
// 计数信号量 最大信号量为3 初始值为0
counting_semaphore<3> csem(0);

// 条件信号量线程
void task0()
{
    cout << "等待获取信号量\n" ;
    // 如果信号量的值为0，那么acquire方法会阻塞线程。
    // 如果信号量的值为 1，则将信号量的值置为0，同时线程会继续执行
    bsem.acquire();
    cout << "线程继续运行\n";
}
// 计数信号量线程
void task1()
{
    cout << "等待获取信号量\n";
    csem.acquire();
    cout << "线程继续运行\n";
}
// 条件信号量
void binary() {
    thread t(task0);
    cout << "准备释放信号量\n";
    // release方法来释放信号量，这会使信号量的值加1
    bsem.release();
    cout << "释放信号量完成\n";
    t.join();
}
// 计数信号量
void counting() {
    thread t0(task1);
    thread t1(task1);
    thread t2(task1);
    thread t3(task1);
    thread t4(task1);
    cout << "准备释放信号量\n";
    // 信号量的值加2,这意味着有2个线程可以成功获取到信号量并继续执行,其他线程仍然被阻塞，直到更多的信号量被释放
    csem.release(2);
    cout << "释放信号量完成\n";
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}
int main()
{
    //binary();
    counting();
    return 0;
}
