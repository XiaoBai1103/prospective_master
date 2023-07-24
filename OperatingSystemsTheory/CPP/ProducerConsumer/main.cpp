/*
    ���ߣ�btx
    �������ڣ�23-7-18
    ���ܣ������ߺ�������ģ��
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
        // ֱ��дthread(Producer)�Ǵ����
        // lambda���ʽ���Ա���������⣬����Ϊ��������һ�������������󣬶�����һ����ʱ����
        // ��������������һ����lambda���ʽҲ�������������ڱ��ֶ��ⲿ���������ã���˼�ʹ��std::thread����֮��lambda���ʽ��Ȼ���Է��ʶ���
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
    // ������
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
            // ֪ͨ�ȴ��е���������
            condVar.notify_one();
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    void Consumer() {
        while (true) {
            unique_lock<mutex> lock(mutex_);
            // �ȴ���������condVar��֪ͨ
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