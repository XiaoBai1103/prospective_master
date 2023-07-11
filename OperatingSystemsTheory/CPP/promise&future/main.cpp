/*
    ���ߣ�btx
    �������ڣ�23-7-7
    ���ܣ�promise & future
*/
#include <iostream>  
#include <thread>  
#include <future>
using namespace std;

void task(shared_future<int>& b) {
    cout << "����ֵΪ"<<b.get()<<endl;
}
int main()
{
    promise<int> p_in;
    future<int> f_in = p_in.get_future();

    // future��get()ֻ��ִ��һ�Σ�����ᱨ��
    shared_future<int> s_f = f_in.share();

    thread t0(task, ref(s_f));
    thread t1(task, ref(s_f));
    thread t2(task, ref(s_f));
    thread t3(task, ref(s_f));
    // ִ�������������̲߳�����Ϊ��δ���p_in��ֵ������
    // ......
    // Ϊpromise��ֵ
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
    // future��get()ֻ��ִ��һ�Σ�����ᱨ��
    cout << "������:" << f.get() << endl;
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

    // ref(p)��ʾ��promise<int>����p�����ô��ݸ�����
    thread t(task, 1, ref(f_in), ref(p_ret));
    // ִ�������������̲߳�����Ϊ��δ���p_in��ֵ������
    // ......
    // Ϊpromise��ֵ
    p_in.set_value(2);
    // ......
    cout << "������:" << f_ret.get() << endl;
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

    // future��get()ֻ��ִ��һ�Σ�����ᱨ��
    shared_future<int> s_f = f_in.share();


    // ref(p)��ʾ��promise<int>����p�����ô��ݸ�����
    thread t0(task, 1, s_f, ref(p_ret));
    thread t1(task, 1, s_f, ref(p_ret));
    thread t2(task, 1, s_f, ref(p_ret));
    thread t3(task, 1, s_f, ref(p_ret));
    // ִ�������������̲߳�����Ϊ��δ���p_in��ֵ������
    // ......
    // Ϊpromise��ֵ
    p_in.set_value(2);
    // ......
    cout << "������:" << f_ret.get() << endl;
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
*/

