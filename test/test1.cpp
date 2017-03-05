#include <boost/optional.hpp>
#include <iostream>

#include "optional_monad/optional_monad.h"
#include "TestClass.h"

auto foo(const TestClass& x) -> TestClass {
    return TestClass(x.value * 2);
}

auto foo_which_might_fail(const TestClass& x) -> boost::optional<TestClass> {
    return TestClass(x.value * 2);
}

void foo_mutate_in_place(TestClass& x) {
    x.value *= 2;
}

void immutable_map_test() {
    std::cout << std::endl << "--- " << __PRETTY_FUNCTION__ << std::endl;
    boost::optional<TestClass> x(5);
    auto y = fmap(x, foo);
    std::cout << "x = " << x.value().value << std::endl;
    std::cout << "y = " << y.value().value << std::endl;
}

//void immutable_map_operator_test() {
//    std::cout << std::endl << "--- " << __PRETTY_FUNCTION__ << std::endl;
//    boost::optional<TestClass> x(5);
//    auto y = x >> foo;
//    std::cout << "x = " << x.value().value << std::endl;
//    std::cout << "y = " << y.value().value << std::endl;
//}

void immutable_bind_test() {
    std::cout << std::endl << "--- " << __PRETTY_FUNCTION__ << std::endl;
    boost::optional<TestClass> x(5);
    auto y = bind(x, foo_which_might_fail);
    std::cout << "x = " << x.value().value << std::endl;
    std::cout << "y = " << y.value().value << std::endl;
}

void immutable_bind_operator_test() {
    std::cout << std::endl << "--- " << __PRETTY_FUNCTION__ << std::endl;
    boost::optional<TestClass> x(5);
    auto y = x >> foo_which_might_fail;
    std::cout << "x = " << x.value().value << std::endl;
    std::cout << "y = " << y.value().value << std::endl;
}

void mutable_with_test() {
    std::cout << std::endl << "--- " << __PRETTY_FUNCTION__ << std::endl;
    boost::optional<TestClass> x(5);
    std::cout << "before x = " << x.value().value << std::endl;
    with(x, foo_mutate_in_place);
    std::cout << "after x = " << x.value().value << std::endl;
}

void mutable_with_movable_test() {
    std::cout << std::endl << "--- " << __PRETTY_FUNCTION__ << std::endl;
    boost::optional<TestClass> x(5);
    std::cout << "before x = " << x.value().value << std::endl;
    auto y = with(std::move(x), foo_mutate_in_place);
    std::cout << "after x = " << x.value().value << std::endl;
    std::cout << "y = " << y.value().value << std::endl;
}

int main() {
    immutable_map_test();
    //immutable_map_operator_test();
    immutable_bind_test();
    immutable_bind_operator_test();
    mutable_with_test();
    mutable_with_movable_test();
}
