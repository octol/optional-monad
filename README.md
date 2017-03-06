optional-monad
==============

A minimal C++ library providing a few functions to be able to work with
boost/std::optional as a monad.

fmap
----

The `fmap` function applies the function object to the wrapped value, from
which it creates and returns a new optional. Very loosely speaking, this makes
the pair `(optional<T>, fmap)` a functor.

```haskell
fmap :: optional T  -> (T -> S) -> optional S
```

```c++
auto fmap(const optional<T>& opt, Func&& func) -> optional<decltype(func(*opt))>;
```

bind
----

The `bind` function applies the function object to the wrapped value, unwraps
one layer of `optional<T>` and returns a new `optional`. The pair
`(optional<T>, bind)` is, again very loosely speaking, a monad.

```haskell
bind :: optional T -> (T -> optional S) -> optional S
```

```c++
auto bind(const optional<T>& opt, Func&& func) -> decltype(func(*opt));
```

with
----

The `with` function is sort of a special case for when you want to mutate the
wrapped value in-place.

```haskell
with :: optional T& -> (T -> void) -> void
```

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
- Add examples to README.

Jon Haggblad <jon@haeggblad.com>

Last update: 05 March 2017
