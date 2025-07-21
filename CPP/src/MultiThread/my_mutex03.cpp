#include <iostream>
#include <array>
#include <thread>
#include <mutex>

const int N = 1e6;

class Counter {
private:
    std::mutex counter_mutex;
    int m_counter = 0;
public:
    void inc() {
        std::lock_guard lock(counter_mutex);
        ++ m_counter;
    }
    int get() {
        std::lock_guard lock(counter_mutex);
        return m_counter;
    }
};

int main() {
    Counter counter;
    auto increase = [](Counter &counter) {
        for (int i = 0; i < N; ++ i) counter.inc();
    };
    std::thread thread_1(increase, std::ref(counter));
    std::thread thread_2(increase, std::ref(counter));
    thread_1.join();
    thread_2.join();

    std::cout << "counter = " << counter.get() << '\n';
    return 0;
}