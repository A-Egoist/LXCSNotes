#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <numbers>
#include <limits>
#include <iomanip>
using namespace std::chrono_literals;

struct SharedContent {
    using high_resolution_clock = std::chrono::high_resolution_clock;
    using float_seconds = std::chrono::duration<float, std::chrono::seconds::period>;
public:
    SharedContent() {
        startTime = high_resolution_clock::now();
    }
    void write() {
        std::srand(std::time(nullptr));
        int random_number = std::rand();
        std::stringstream stream;
        stream << "rn = " << random_number << "\n";
        
        std::lock_guard lock(mtx);
        content = stream.str();
        print("write");
        std::this_thread::sleep_for(1s);  // 模拟耗时操作
    }
    void read() {
        // std::lock_guard lock(mtx);
        std::shared_lock lock(mtx);
        print("read");
        std::this_thread::sleep_for(500ms);  // 模拟耗时时间
    }
private:
    float elapsed_time() {
        return float_seconds(high_resolution_clock::now() - startTime).count();
    }
    template<class T>
    void print(T &&rw) {
        std::lock_guard lock2(cout_mtx);
        std::cout << std::fixed << std::setprecision(2) << std::setw(7) << elapsed_time() << "s:[tid:" << std::this_thread::get_id() << "][" << std::setw(5) << rw << "]" << content << std::endl;
    }
    // std::mutex mtx;
    std::shared_mutex mtx;
    std::mutex cout_mtx;
    std::string content = "no data\n";
    high_resolution_clock::time_point startTime;
};

int main() {
    SharedContent content;

    auto write = [&content]() {
        for (int i = 0; i < 1000; ++ i) {
            content.write();
            std::this_thread::sleep_for(1ms);
        }
    };
    auto read = [&content]() {
        for (int i = 0; i < 1000; ++ i) {
            content.read();
            std::this_thread::sleep_for(1ms);
        }
    };

    std::thread w_th(write);
    std::vector<std::thread> r_threads;
    for (int i = 0; i < 4; ++ i) {
        r_threads.emplace_back(read);
    }

    w_th.join();
    for (auto &t: r_threads) t.join();

    return 0;
}