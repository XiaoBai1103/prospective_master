/*
    作者：btx
    创建日期：23-7-18
    功能：生产者和消费者模型
*/
#include <iostream>  
#include <queue>  
#include <thread>  
#include <mutex>  
#include <condition_variable>  
using namespace std;
class ProducerConsumer {
public:
    ProducerConsumer(int max_queue_size) : max_queue_size_(max_queue_size) {}

    void StartProducerThread() {
        // 直接写thread(Producer)是错误的
        // lambda表达式可以避免这个问题，是因为它创建了一个匿名函数对象，而不是一个临时对象。
        // 与其他函数对象一样，lambda表达式也在其生命周期内保持对外部变量的引用，因此即使在std::thread销毁之后，lambda表达式仍然可以访问队列
        producer_thread = thread([this]() { Producer(); });
    }

    void StartConsumerThread() {
        consumer_thread = thread([this]() { Consumer(); });
    }

    void StopProducerThread() {
        if (producer_thread.joinable()) {
            producer_thread.join();
        }
    }

    void StopConsumerThread() {
        if (consumer_thread.joinable()) {
            consumer_thread.join();
        }
    }

private:
    int max_queue_size_;
    // 缓冲区
    queue<int> queue;
    mutex mutex_;
    condition_variable condVar;
    thread producer_thread;
    thread consumer_thread;

    void Producer() {
        int value = 0;
        while (true) {
            unique_lock<mutex> lock(mutex_);
            condVar.wait(lock, [this]() { return queue.size() < max_queue_size_; });
            value++;
            cout << "Produced: " << value << endl;
            queue.push(value);
            lock.unlock();
            // 通知等待中的条件变量
            condVar.notify_one();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    void Consumer() {
        while (true) {
            unique_lock<mutex> lock(mutex_);
            // 等待条件变量condVar的通知
            condVar.wait(lock, [this]() { return !queue.empty(); });
            int value = queue.front();
            queue.pop();
            lock.unlock();
            cout << "Consumed: " << value << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }
};

int main() {
    ProducerConsumer pc(5);
    pc.StartProducerThread();
    pc.StartConsumerThread(); 
    pc.StopProducerThread();
    pc.StopConsumerThread();
    return 0;
}