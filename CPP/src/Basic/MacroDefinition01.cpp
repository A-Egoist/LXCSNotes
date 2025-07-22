#include <iostream>

#define LOG(o, ...) fprintf(o, "[%s:%d]", __FILE__, __LINE__); fprintf(o, __VA_ARGS__)

int main() {
    LOG(stdout, "%s\n", "测试信息, 日志001");
    // fprintf(__stdoutp, "[%s:%d]", "/Users/amonologue/Project/Notes/CPP/src/Basic/MacroDefinition.cpp", 6);
    // fprintf(__stdoutp, "%s\n", "测试信息, 日志001");
}