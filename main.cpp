#include <bits/stdc++.h>

#include "common_containers/seq_container/list/allocator.h"

#include <chrono>
#include <iostream>
#include <string>

class LogDuration {
public:
    explicit LogDuration(const std::string& msg = "")
        : message_(msg), start_(std::chrono::steady_clock::now()) {}

    ~LogDuration() {
        using namespace std::chrono;
        auto finish = steady_clock::now();
        auto duration = duration_cast<milliseconds>(finish - start_).count();
        std::cerr << message_ << " took " << duration << " ms\n";
    }

private:
    std::string message_;
    std::chrono::steady_clock::time_point start_;
};

#define LOG_DURATION(message) LogDuration guard(message);

void test_stack_allocator() {
    s21::StackStorage<100000> storage;
    s21::StackAllocator<int, 100000> stack_alloc(storage);

    LOG_DURATION("StackAllocator test");
    std::vector<int, s21::StackAllocator<int, 100000>> v(stack_alloc);

    for (int i = 0; i < 10000; ++i) {
        v.push_back(i);
        // std::cout << i << std::endl;
    }
}

void test_std_allocator() {
    LOG_DURATION("std::allocator test");
    std::vector<int> v;

    for (int i = 0; i < 50000; ++i) {
        v.push_back(i);
    }
}

int main() {
    test_stack_allocator();
    test_std_allocator();
    return 0;
}
