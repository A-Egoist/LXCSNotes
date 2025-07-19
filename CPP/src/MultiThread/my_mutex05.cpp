#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std::chrono_literals;

class DemoClass {
public:
    void func1() {
        {
            std::scoped_lock lock(mtx1, count_mtx);
            ++ count;
            std::cout << "[func1] Count = " << count << "\n";
        }
        std::this_thread::sleep_for(1ms);
    }
    void func2() {
        {
            std::scoped_lock lock(count_mtx, mtx1);
            -- count;
            std::cout << "[func2] Count = " << count << "\n";
        }
        std::this_thread::sleep_for(1ms);
    }
    void calc(int n) {
        for (int i = 0; i < n; ++ i) {
            if (n % 2) func2();
            else func1();
        }
    }
private:
    std::mutex mtx1;
    std::mutex count_mtx;
    int count = 0;
};

int main() {
    DemoClass demo;
    const int N1 = 1e6;
    const int N2 = 1e6 + 1;
    std::thread th1(&DemoClass::calc, &demo, N1);
    std::thread th2(&DemoClass::calc, &demo, N2);
    th1.join();
    th2.join();

    return 0;
}