#include <iostream>
#include <vector>
#include <array>
#include <thread>

template <typename Iter, typename UnaryOp, typename BinaryOp, typename Result>
void transform_reduce(Iter first, Iter last, UnaryOp transform, BinaryOp reduce, Result &result) {
    for (auto it = first; it != last; ++ it) {
        result = reduce(result, transform(*it));
    }
}

int main() {
    const int N = 10000;
    std::vector<double> numbers;
    numbers.reserve(N);

    // for (int i = 0; i < N; ++ i) numbers.push_back((double) i / N);
    for (int i = 0; i < N; ++ i) numbers.push_back(1.0 * i / N);

    auto transform = [](double x) { return x * x; };
    auto reduce = [](double a, double b) { return a + b; };

    const int N_thread = 8;  // 假设有 8 个 cpu cores
    std::vector<std::thread> workers;  // 工作线程
    std::array<double, N_thread> subResult{0};  // 保存每个工作线程的结果

    for (int i = 0; i < N_thread; ++ i) {
        auto low = numbers.begin() + i * numbers.size() / N_thread;
        auto high = numbers.begin() + (i + 1) * numbers.size() / N_thread;

        workers.push_back(
            std::thread(
                transform_reduce<std::vector<double>::iterator, decltype(transform), decltype(reduce), double>,
                low, high, transform, reduce, std::ref(subResult[i])
            )
        );
    }

    // 汇总结果
    double result = 0;
    for (int i = 0; i < N_thread; ++ i) {
        workers[i].join();  // 等待工作线程执行结束
        result = reduce(result, subResult[i]);
    }

    std::cout << result << std::endl;

    return 0;
}