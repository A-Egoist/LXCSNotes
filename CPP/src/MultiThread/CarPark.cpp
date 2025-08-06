#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <sstream>
#include <vector>
#include <semaphore>
#include <array>
#include <random>
#include <string>

template<std::size_t N = 10>
class CarPark {
public:
    CarPark(): sem(N) {}
    int enter() {
        printf("[%d]准备进入停车场\n", std::this_thread::get_id());
        sem.acquire();
        std::lock_guard lock(mutex_);
        printf("[%d]进入停车场\n", std::this_thread::get_id());
        for (int i = 0; i < N; ++ i) {
            if (spaces[i].empty()) {
                std::stringstream ss;
                ss << std::this_thread::get_id();
                spaces[i] = ss.str();
                printf("[%s]找到停车位#%d\n", ss, i);
                return i;
            }
        }
        throw(std::runtime_error("程序异常到达此处"));
    }

private:
    std::array<std::string, N> spaces;
    std::counting_semaphore<N> sem;
    std::mutex mutex_;
    Random rn{500, 5000};
};

int main() {
    return 0;
}