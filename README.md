optional-monad
==============

A minimal C++ library providing a few functions to be able to work with
boost/std::optional as a monad.

fmap:

```c++
auto fmap(const optional<T>& opt, Func&& func) -> optional<decltype(func(*opt))>;
```

bind:

```c++
auto bind(const optional<T>& opt, Func&& func) -> decltype(func(*opt));
```

with:

```c++
void with(optional<T>& opt, const Func& func);
```

TODO
----

- Wrap in a suitable namespace (what name? `optm`, `optmonad`, `omonad`,
  `omon`, `opt_monad`, `optional_monad`?)
- Convert test to actual unit tests (let's try Catch).
- Hook up unit tests to CI system (Travis-CI?)
- Proper cross-platform build system (probably CMake).
- Currently hardcoded for `boost::optional`. Make it work with `std::optional`
  out-of-the-box.

Jon Haggblad <jon@haeggblad.com>

Last update: 05 March 2017
