#pragma once

#include <iostream>

class TestClass {
public:
    TestClass() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    TestClass(int val) : value(val) {
        std::cout << __PRETTY_FUNCTION__ << ": " << val << std::endl;
    }
    ~TestClass() {
        std::cout << __PRETTY_FUNCTION__ << ": " << value << std::endl;
    }
    TestClass(const TestClass& rhs) : value(rhs.value) {
        std::cout << __PRETTY_FUNCTION__ << ": " << value << std::endl;
    }
    TestClass& operator=(const TestClass& rhs) {
        value = rhs.value;
        std::cout << __PRETTY_FUNCTION__ << ": " << value << std::endl;
        return *this;
    }
    TestClass(TestClass&& rhs)  {
        value = rhs.value;
        rhs.value = 0;
        std::cout << __PRETTY_FUNCTION__ << ": " << value << std::endl;
    }
    TestClass& operator=(TestClass&& rhs) {
        (void)rhs;
        std::cout << __PRETTY_FUNCTION__ << ": " << value << std::endl;
        return *this;
    }

    int value = 0;
};

