#include <iostream>
#include <vector>
#include <array>
#include <thread>

template <typename Iter, typename UnaryOp, typename BinaryOp, typename Result, std::size_t MinDist = 100>
void transform_reduce(Iter first, Iter last, UnaryOp transform, BinaryOp reduce, Result &result) {
    std::size_t distance = std::distance(first, last);
    if (distance <= MinDist) {
        for (auto it = first; it != last; ++ it) {
            result = reduce(result, transform(*it));
        }
    } else {
        std::size_t half = distance / 2;
        Iter middle = first + half;

        Result r_result = 0;
        Result l_result = 0;

        std::thread l_thread(transform_reduce<Iter, UnaryOp, BinaryOp, Result>, first, middle, transform, reduce, std::ref(l_result));
        std::thread r_thread(transform_reduce<Iter, UnaryOp, BinaryOp, Result>, middle, last, transform, reduce, std::ref(r_result));

        l_thread.join();
        r_thread.join();
        result = reduce(result, reduce(l_result, r_result));
    }
}

int main() {
    const int N = 10000;
    std::vector<double> numbers;
    numbers.reserve(N);

    for (int i = 0; i < N; ++ i) numbers.push_back(1.0 * i / N);

    auto transform = [](double x) { return x * x; };
    auto reduce = [](double a, double b) { return a + b; };

    double result = 0;
    auto first = numbers.begin();
    auto last = numbers.end();
    std::thread root_thread(transform_reduce<std::vector<double>::iterator, decltype(transform), decltype(reduce), double>, first, last, transform, reduce, std::ref(result));
    root_thread.join();
    std::cout << result << std::endl;

    return 0;
}