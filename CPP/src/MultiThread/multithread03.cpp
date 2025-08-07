#include <iostream>
#include <thread>
#include <array>

void greeting(int idx) {
    // std::cout << "Hello from thread" << idx << std::endl;
    printf("Hello from thread %d\n", idx);  // printf 
}

int main() {
    const int N = 10;
    std::array<std::thread, N> workers;
    for (int i = 0; i < N; ++ i) {
        workers[i] = std::thread(greeting, i);
    }

    for (auto &worker: workers) {
        worker.join();
    }

    return 0;
}