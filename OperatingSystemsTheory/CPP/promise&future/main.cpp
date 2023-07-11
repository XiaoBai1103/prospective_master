/*
    作者：btx
    创建日期：23-7-7
    功能：promise & future
*/
#include <iostream>  
#include <thread>  
#include <future>
using namespace std;

void task(shared_future<int>& b) {
    cout << "传入值为"<<b.get()<<endl;
}
int main()
{
    promise<int> p_in;
    future<int> f_in = p_in.get_future();

    // future的get()只能执行一次，否则会报错
    shared_future<int> s_f = f_in.share();

    thread t0(task, ref(s_f));
    thread t1(task, ref(s_f));
    thread t2(task, ref(s_f));
    thread t3(task, ref(s_f));
    // 执行其他任务，主线程不会因为还未获得p_in的值而阻塞
    // ......
    // 为promise幅值
    p_in.set_value(2);
    // ......
 
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    return 0;
}





/*

void task(int a, int b, promise<int>& ret) {
    int ret_a = a * a;
    int ret_b = b * 2;
    ret.set_value(ret_a + ret_b);
}
int main()
{
    int ret = 0;
    promise<int> p;
    future<int> f = p.get_future();
    thread t(task, 1, 2, ref(p));
    // future的get()只能执行一次，否则会报错
    cout << "计算结果:" << f.get() << endl;
    t.join();
    return 0;
}






void task(int a,future<int>& b, promise<int>& ret) {
    int ret_a = a * a;
    int ret_b = b.get() * 2;
    ret.set_value(ret_a + ret_b);
}
int main()
{
    int ret = 0;

    promise<int> p_ret;
    future<int> f_ret = p_ret.get_future();

    promise<int> p_in;
    future<int> f_in = p_in.get_future();

    // ref(p)表示将promise<int>对象p的引用传递给函数
    thread t(task, 1, ref(f_in), ref(p_ret));
    // 执行其他任务，主线程不会因为还未获得p_in的值而阻塞
    // ......
    // 为promise幅值
    p_in.set_value(2);
    // ......
    cout << "计算结果:" << f_ret.get() << endl;
    t.join();
    return 0;
}






void task(int a,shared_future<int>& b, promise<int>& ret) {
    int ret_a = a * a;
    int ret_b = b.get() * 2;
    ret.set_value(ret_a + ret_b);
}
int main()
{
    int ret = 0;

    promise<int> p_ret;
    future<int> f_ret = p_ret.get_future();

    promise<int> p_in;
    future<int> f_in = p_in.get_future();

    // future的get()只能执行一次，否则会报错
    shared_future<int> s_f = f_in.share();


    // ref(p)表示将promise<int>对象p的引用传递给函数
    thread t0(task, 1, s_f, ref(p_ret));
    thread t1(task, 1, s_f, ref(p_ret));
    thread t2(task, 1, s_f, ref(p_ret));
    thread t3(task, 1, s_f, ref(p_ret));
    // 执行其他任务，主线程不会因为还未获得p_in的值而阻塞
    // ......
    // 为promise幅值
    p_in.set_value(2);
    // ......
    cout << "计算结果:" << f_ret.get() << endl;
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
*/

