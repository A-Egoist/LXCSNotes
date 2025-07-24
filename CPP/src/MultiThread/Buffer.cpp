#include <iostream>
#include <semaphore>
#include <mutex>
#include <thread>
#include <array>
#include <random>
#include <chrono>
#include <sstream>
#include <string>

template <size_t bufferSize = 6>
class RWBuffer {
public:
    RWBuffer(): char_gen('A', 'Z'), write_delay_gen(500, 1000), read_delay_gen(800, 1500), sem_reader(0), sem_writer(bufferSize) { buffer.fill(' '); }
    char prepareData() {
        std::this_thread::sleep_for(std::chrono::microseconds(write_delay_gen()));  // 模拟生成数据消耗的时间
        return static_cast<char>(char_gen());
    }
    void processData(char ch) {
        std::this_thread::sleep_for(std::chrono::microseconds(read_delay_gen()));  // 模拟处理数据消耗的时间
    }
    void printBuffer() {
        std::stringstream ss;
        ss << "Buffer: |";
        for (auto &ch: buffer) ss << ch << "|";
        printf("%s\n", ss.str().c_str());
        // std::cout << ss.str() << std::endl;
    }
    void writerToBuffer(size_t iterations) {
        printf("写线程就绪.\n");
        for (size_t i = 0; i < iterations * buffer.size(); ++ i) {
            char ch = prepareData();
            sem_writer.acquire();
            buffer[i % buffer.size()] = ch;
            printf("写线程: 写入字符%c.\t", ch);
            printBuffer();
            sem_reader.release();
        }
    }
    void readFromBuffer(size_t iterations) {
        printf("读线程就绪.\n");
        for (size_t i = 0; i < iterations * buffer.size(); ++ i) {
            sem_reader.acquire();
            auto idx = i % buffer.size();
            char ch = buffer[idx];
            processData(ch);
            buffer[idx] = ' ';
            printf("读线程: 读取字符%c.\t", ch);
            printBuffer();
            sem_writer.release();
        }
    }
private:
    // 随机数生成器封装
    class RandomInt {
    public:
        RandomInt(int min, int max) : 
            distribution(min, max), 
            generator(std::random_device{}()) {}

        int operator()() {
            return distribution(generator);
        }

    private:
        std::uniform_int_distribution<> distribution;
        std::mt19937 generator;
    };
    RandomInt write_delay_gen;  // 写延迟
    RandomInt read_delay_gen;  // 读延迟
    RandomInt char_gen{'A', 'Z'};
    std::array<char, bufferSize> buffer;
    std::counting_semaphore<bufferSize> sem_reader{0};
    std::counting_semaphore<bufferSize> sem_writer{bufferSize};
};
int main() {
    RWBuffer buffer;
    const size_t iterations = 3;
    std::thread write_thread(&RWBuffer<>::writerToBuffer, &buffer, iterations);
    std::thread read_thread(&RWBuffer<>::readFromBuffer, &buffer, iterations);

    write_thread.join();
    read_thread.join();

    return 0;
}