# The C++ CP Template
---
- [Modular Class](#modular-class)
- [Fenwick Tree](#fenwick-tree)
---
## [Modular Class](/modular.cpp)
```cpp
using Mod = modular<ll, (ll)1e9+7>;
```

## [Fenwick Tree](/fenwick_tree.cpp)
```cpp
template<class T, class trait> fenwick_tree;

template<class T> struct fenwick_tree_op {
  // merge(l, r)
  // merge values of [l] and [r] or bit array and update value
  virtual T merge(const T&, const T&) = 0;

  // sub(l, r)
  // subtract values of [1, l) and [1, r] => become [l, r]
  virtual T sub(const T&, const T&) = 0;
};

fenwick_tree<int, fenwick_tree_add<int>> tree(N);
```