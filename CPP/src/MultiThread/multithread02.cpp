#include <iostream>
#include <thread>
#include <string>

void hello(const std::string &name) {
    std::cout << "Hello, " << name << ". [Thread ID = " << std::this_thread::get_id() << "]\n";
}

int main() {
    std::cout << "Main function. [Thread ID = " << std::this_thread::get_id() << "]\n";
    std::thread mythread(hello, std::string("World"));
    if (mythread.joinable())
        mythread.join();

    return 0;
}