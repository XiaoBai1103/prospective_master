/*
    作者：btx
    日期：23-6-24
    功能：条件变量
*/
#include <iostream>  
#include <thread>  
#include <mutex>  
#include <condition_variable>  

std::mutex mtx;
std::condition_variable cv;

void workerThread() {
    std::unique_lock<std::mutex> lock(mtx);
    //等待条件变量的信号，如果条件变量没有信号，则线程会进入等待状态，
    //此时会释放互斥锁lock，直到条件变量cv被唤醒，并重新获得互斥锁lock，继续执行
    cv.wait(lock); // 等待条件变量  
    std::cout << "Worker thread is awake!" << std::endl;
}

void mainThread() {
    {
        std::lock_guard<std::mutex> lock(mtx);  
    }
    cv.notify_one(); // 唤醒等待条件变量的线程  
}

int main() {
    std::thread worker(workerThread);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::thread main(mainThread);
    worker.join();
    main.join();
    return 0;
}