/*
    ���ߣ�btx
    ���ڣ�23-6-24
    ���ܣ���������
*/
#include <iostream>  
#include <thread>  
#include <mutex>  
#include <condition_variable>  

std::mutex mtx;
std::condition_variable cv;

void workerThread() {
    std::unique_lock<std::mutex> lock(mtx);
    //�ȴ������������źţ������������û���źţ����̻߳����ȴ�״̬��
    //��ʱ���ͷŻ�����lock��ֱ����������cv�����ѣ������»�û�����lock������ִ��
    cv.wait(lock); // �ȴ���������  
    std::cout << "Worker thread is awake!" << std::endl;
}

void mainThread() {
    {
        std::lock_guard<std::mutex> lock(mtx);  
    }
    cv.notify_one(); // ���ѵȴ������������߳�  
}

int main() {
    std::thread worker(workerThread);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::thread main(mainThread);
    worker.join();
    main.join();
    return 0;
}