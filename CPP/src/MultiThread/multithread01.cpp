#include <iostream>
#include <thread>

void myFunc(double param1, double param2, double &result) {
    result = param1 + param2;
}

struct MyStruct {
    // void operator()(double param1, double param2) {
    //     result = param1 + param2;
    // }
    void sum(double param1, double param2) {
        result = param1 + param2;
    }
    double result = 0;
};

class MyClass {
public:
    void sum(double param1, double param2) {
        result = param1 + param2;
    }
    double result = 0;
};

int main() {
    double a = 1.1;
    double b = 3.2;
    double result = 0;

    std::thread thread1(myFunc, a, b, std::ref(result));

    MyStruct my_struct;
    // std::thread thread2(std::ref(my_struct), a, b);
    std::thread thread2(&MyStruct::sum, &my_struct, a, b);

    MyClass my_class;
    std::thread thread3(&MyClass::sum, &my_class, a, b);

    double result2;
    std::thread thread4([&result2](double a, double b) { result2 = a + b; }, a, b);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    printf("In thread1, result = %.2f\n", result);
    printf("In thread2, my_struct.result = %.2f\n", my_struct.result);
    printf("In thread3, result = %.2f\n", my_class.result);
    printf("In thread4, result2 = %.2f\n", result2);
    return 0;
}