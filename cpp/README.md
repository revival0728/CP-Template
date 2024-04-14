# The C++ CP Template
---
- [Modular Class](#modular-class)
- [Fenwick Tree](#fenwick-tree)
- [Vector Deque](#vector-deque)
---
## [Modular Class](/cpp/modular.cpp)
```cpp
using Mod = modular<ll, (ll)1e9+7>;
```

## [Fenwick Tree](/cpp/fenwick_tree.cpp)
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

fenwick_tree<int, trait::fenwick_tree_add<int>> tree(N);
```

## [Segment Tree](/cpp/segment_tree.cpp)
```cpp
template<class T, class trait, class Tt> segment_tree;

template<class T, class Tt = int> struct segment_tree_op {
  // nan()
  // return out of boundary value
  virtual constexpr T nan() = 0;

  // merge(l, r)
  // merge values of [l] and [r]
  virtual T merge(const T&, const T&) = 0;
};
```

Example by template
```cpp
using namespace trait::segment_tree;

struct tree_trait : public segment_tree_add<int>, range_update<int>, update_by_set<int>, update_by_single<int> {};
segment_tree<int, tree_trait> tree(N);

struct tree_trait : public segment_tree_max<int>, single_update<int> {};
segment_tree<int, tree_trait> tree(N);
```

## [Vector Deque](/cpp/vec_deq.cpp)
```cpp
vec_deque<int> deq;

deq.push_back(1);  //vec_deq={1}
deq.push_front(0); //vec_deq={0,1}
deq.size();        //size=2
deq[1]             //vec_deq[1]=1
deq.pop_front();   //vec_deq={1}
deq.pop_back();    //vec_deq={}
deq.empty();       //true
```

### Reference
```cpp
vec_deque(int _capacity);
template<class P> void push_back(P val);
template<class P> void push_front(P val);
template<class ...P> void emplace_back(P ...t);
template<class ...P> void emplace_front(P ...t);
size_t size() { return pr - pl; }
void pop_back();
void pop_front();
bool empty();
T& operator[](const size_t i);
T& front();
T& back();
iterator begin();
iterator end();
```