#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

struct Channel {
public:
    void getData() {
        auto tid = std::this_thread::get_id();
        std::unique_lock lock(mutex_);
        std::cout << "接收方[" << tid << "] 等待数据;" << std::endl;
        condition_variable_.wait(lock);
        std::cout << "接收方[" << tid << "] 得到数据;" << std::endl;
        sharedData.clear();
    }
    void setData() {
        static int id = 1;
        std::stringstream ss;
        ss << "Hello #" << id;
        {
            std::unique_lock lock(mutex_);
            sharedData = ss.str();
            std::cout << "\n发送方: 第" << id << "条数据写入完毕;" << std::endl;
            ++ id;
        }
        condition_variable_.notify_one();
        std::this_thread::sleep_for(1ms);
    }
private:
    std::mutex mutex_;
    std::condition_variable condition_variable_;
    std::string sharedData;
};

int main() {
    Channel channel;
    std::thread write_th(&Channel::setData, &channel);
    std::thread read_th(&Channel::getData, &channel);

    write_th.join();
    read_th.join();

    return 0;
}