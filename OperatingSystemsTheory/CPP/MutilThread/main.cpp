#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;
int global_count = 0;
//atomic<int> global_count = 0;
mutex mtx; // 创建互斥锁

void task_1(int num)
{
	for (int i = 0; i < num; i++)
	{
		std::lock_guard<std::mutex> lock(mtx); // 加锁 作用域：整个for循环
		global_count++;
	}
}

void task_2(int num)
{
	for (int i = 0; i < num; i++)
	{
		std::unique_lock<std::mutex> lock(mtx);
		global_count++;
		lock.unlock(); // 手动解锁
	}
}

int main()
{
	thread th1(task_1, 5000);
	thread th2(task_2, 5000);
	// 等待线程完成
	th1.join();
	th2.join();
	cout << "主程序结束 count值为" << global_count << endl;
	return 0;
}