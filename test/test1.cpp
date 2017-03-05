/* MIT License
 *
 * Copyright (c) 2017 Jon Haggblad
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
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
