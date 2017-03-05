optional-monad
==============

A small library providing a few functions to be able to work with
boost/std::optional as a monad.

fmap:

```c++
auto fmap(const optional<T>& opt, Func&& func) -> optional<decltype(func(*opt))>;
```

bind:

```
auto bind(const optional<T>& opt, Func&& func) -> decltype(func(*opt));
```

with:

```
void with(optional<T>& opt, const Func& func);
```

Jon Haggblad <jon@haeggblad.com>

Last update: 05 March 2017
