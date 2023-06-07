/*
	作者：btx
	日期：23-6-3
	内容：多线程
*/
#include <iostream>
#include <thread>
using namespace std;

void task_1(int count) {
	for (int i = 0; i < count; i++) {
		cout << "task1 id="<<this_thread::get_id()<<endl;
	}
}

class Obj {
public:
	void operator()(int count) {
		for (int i = 0; i < count; i++) {
			cout << "task2 id=" << this_thread::get_id() << endl;
		}
	}
};


int main() {
	cout << "主线程 id=" << this_thread::get_id() << endl;
	thread th1(task_1,5);
	thread th2(Obj(),3);
	// 等待线程完成
	th1.join();
	th2.join();
	cout << "主程序结束\n";
	return 0;
}