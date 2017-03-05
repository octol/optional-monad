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
#pragma once
#include <boost/optional.hpp>

// Immutable function fmap
//
// Example:
//
//  int foo(int);
//
//  optional<int> x = 5;
//  optional<int> y = fmap(x, foo);

// Func :: T -> T
template <typename T, typename Func>
auto fmap(const boost::optional<T>& opt, Func&& func)
        -> boost::optional<decltype(func(*opt))> {
    using OutType = boost::optional<decltype(func(*opt))>;
    return (opt) ? OutType(func(*opt)) : boost::none;
}

//template <typename T, typename Func>
//auto operator>>(const boost::optional<T>& opt, Func&& func)
//        -> boost::optional<decltype(func(*opt))> {
//    return fmap(opt, std::forward<Func>(func));
//}

// Immutable function bind
//
// Example:
//
//  optional<int> foo(int);
//
//  optional<int> x = 5;
//  optional<int> y = bind(x, foo);
//
//  optional<int> x = 5;
//  optional<int> y = x >> foo;
//
// Func :: T -> optional<T>
template <typename T, typename Func>
auto bind(const boost::optional<T>& opt, Func&& func) -> decltype(func(*opt)) {
    return (opt) ? func(*opt) : boost::none;
}

template <typename T, typename Func>
auto operator>>(const boost::optional<T>& opt, Func&& func)
        -> decltype(func(*opt)) {
    return bind(opt, std::forward<Func>(func));
}

// Modify in-place
//
// Example:
//
//  void foo(int);
//
//  optional<int> x = 5;
//  with(x, foo);

// Func :: T -> void
template <typename T, typename Func>
void with(boost::optional<T>& opt, const Func& func) {
    if (opt) {
        func(*opt);
    }
}

// Modify in-place
//
// Example:
//
//  void foo(int);
//
//  optional<int> x = 5;
//  optional<int> y = with(std::move(x), foo);

// Func :: T -> void
template <typename T, typename Func>
auto with(boost::optional<T>&& opt, Func&& func) -> boost::optional<T> {
    if (!opt) {
        return boost::none;
    }
    func(*opt);
    return std::move(opt);
}

