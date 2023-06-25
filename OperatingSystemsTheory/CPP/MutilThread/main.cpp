#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;
int global_count = 0;
//atomic<int> global_count = 0;
mutex mtx; // ����������

void task_1(int num)
{
	for (int i = 0; i < num; i++)
	{
		std::lock_guard<std::mutex> lock(mtx); // ���� ����������forѭ��
		global_count++;
	}
}

void task_2(int num)
{
	for (int i = 0; i < num; i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
		global_count++;
		lock.unlock(); // �ֶ�����
	}
}

int main()
{
	thread th1(task_1, 5000);
	thread th2(task_2, 5000);
	// �ȴ��߳����
	th1.join();
	th2.join();
	cout << "��������� countֵΪ" << global_count << endl;
	return 0;
}