/*
생산자/소비자 모델을 구현하는 예제를 설명드리겠습니다. 이 모델에서는 std::queue를 공유 자원으로 사용하고, mutex와 condition_variable을 활용해 스레드 간의 동기화 문제를 해결합니다.

요구사항:

생산자는 1개의 스레드로 동작하며, 큐에 1000개 이하의 데이터가 있을 때만 데이터를 생산하고, 1000개 이상인 경우 대기해야 합니다.
소비자는 3개의 스레드로 동작하며, 큐에 10개 이상의 데이터가 있을 때만 데이터를 소비합니다.
mutex는 반드시 lock management class(예: std::lock_guard 또는 std::unique_lock)를 사용하여 관리해야 합니다.
*/

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <future>
using namespace std::literals;

std::queue<int> Q;
std::mutex mtx;
std::condition_variable cv_producer, cv_consumer;
const size_t MAX_QUEUE_SIZE = 1000;
const size_t MIN_QUEUE_SIZE_TO_CONSUME = 10;
bool done = false;

void producer(std::promise<bool>& pm) {
    int data = 0;
    while (data < 5000) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_producer.wait(lock, []() { return Q.size() < MAX_QUEUE_SIZE; });

        Q.push(data++);
        std::cout << "생산 데이터 : " << data << ", Queue Size : " << Q.size() << std::endl;

        cv_consumer.notify_all();
    }

    std::lock_guard<std::mutex> lock(mtx);
    done = true;
    pm.set_value(done);
    std::cout << ">> 생산 완료." << std::endl;

    cv_consumer.notify_all();
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consumer.wait(lock, []() { return Q.size() >= MIN_QUEUE_SIZE_TO_CONSUME || done; });

        if (done && Q.empty()) {
            std::cout << ">> 소비자[" << id << "] exiting." << std::endl;
            break;
        }

        while (Q.size() >= MIN_QUEUE_SIZE_TO_CONSUME) {
            int data = Q.front();
            Q.pop();
            std::cout << "소비자[" << id << "] 소비 데이터 : " << data << ", Queue Size : " << Q.size() << std::endl;
        }

        cv_producer.notify_all();
    }
}

int main() {

    std::promise<bool> pm;
    std::future<bool> ft = pm.get_future();

    // 생산자 스레드 1개
    std::thread th_producer(producer, std::ref(pm));

    // 소비자 스레드 3개
    std::thread th_consumer[3];
    for (int i = 0; i < 3; i++) {
        th_consumer[i] = std::thread(consumer, i+1);
    }

    // 모든 스레드가 작업을 끝날때까지 대기
    th_producer.join();
    std::cout << ">> 생산자 thread 작업완료" << std::endl;
    for (int i = 0; i < 3; i++) {
        if (ft.get())
            break;
        th_consumer[i].join();   
    }
    std::cout << ">> 생산자 thread 작업 완료로 인한 주 thread 작업 종료" << std::endl;

    return 0;
}