#include <iostream>
#include <array>
#include <thread>
const int N = 1e6;

void sum(int &res) {
    // for (int i = 0; i < N; ++ i) res ++;
    for (int i = 0; i < N; ++ i) ++ res;
}

int main() {
    int counter = 0;
    std::thread thread_1(sum, std::ref(counter));
    std::thread thread_2(sum, std::ref(counter));
    thread_1.join();
    thread_2.join();

    std::cout << "counter = " << counter << '\n';
    return 0;
}