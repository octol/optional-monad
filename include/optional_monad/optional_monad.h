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

