/*
    ���ߣ�btx
    �������ڣ�23-6-30
    ���ܣ��ź���semaphore 
*/
#include <iostream>  
#include <thread>  
#include <semaphore>
using namespace std;

// semaphore�ĳ�Ա����
// release �൱��condition_variable�е�֪ͨ(notify)
// acquire �൱��condition_variable�еĵȴ�(wait)

// �����ź���(�������ź����� ��ʼֵΪ0
// ���ź�����ֵΪ0ʱ����ʾ��Դ�ѱ�ռ�û򲻿��ã������߳���Ҫ�ȴ���
// ���ź�����ֵΪ1ʱ����ʾ��Դ���û���У������߳̿��Ի�ȡ��ʹ�ø���Դ��
binary_semaphore bsem(0);
// �����ź��� ����ź���Ϊ3 ��ʼֵΪ0
counting_semaphore<3> csem(0);

// �����ź����߳�
void task0()
{
    cout << "�ȴ���ȡ�ź���\n" ;
    // ����ź�����ֵΪ0����ôacquire�����������̡߳�
    // ����ź�����ֵΪ 1�����ź�����ֵ��Ϊ0��ͬʱ�̻߳����ִ��
    bsem.acquire();
    cout << "�̼߳�������\n";
}
// �����ź����߳�
void task1()
{
    cout << "�ȴ���ȡ�ź���\n";
    csem.acquire();
    cout << "�̼߳�������\n";
}
// �����ź���
void binary() {
    thread t(task0);
    cout << "׼���ͷ��ź���\n";
    // release�������ͷ��ź��������ʹ�ź�����ֵ��1
    bsem.release();
    cout << "�ͷ��ź������\n";
    t.join();
}
// �����ź���
void counting() {
    thread t0(task1);
    thread t1(task1);
    thread t2(task1);
    thread t3(task1);
    thread t4(task1);
    cout << "׼���ͷ��ź���\n";
    // �ź�����ֵ��2,����ζ����2���߳̿��Գɹ���ȡ���ź���������ִ��,�����߳���Ȼ��������ֱ��������ź������ͷ�
    csem.release(2);
    cout << "�ͷ��ź������\n";
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
