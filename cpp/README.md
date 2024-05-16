# The C++ CP Template
---
## Snippet
- [Modular Class](#modular-class): modular
- [Fenwick Tree](#fenwick-tree): fenwick
- [Segment Tree](#segment-tree): segment
- [Geometry](#geometry)
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

template<class T, class Tt = T> struct segment_tree_op {
  // check()
  // return segment tree update method
  // 0 -> single update
  // 1 -> range update
  virtual int check() = 0;

  // nan()
  // return out of boundary value
  virtual T nan() = 0;

  // merge(l, r)
  // merge values of [l] and [r]
  virtual T merge(T, T) = 0;

  // upd(seg, tag, l, r)
  // update seg value by tag value and interval [l, r]
  virtual T upd(T seg, Tt tag, int l, int r) = 0;

  // push(current_tag, parent_tag)
  // update current tag value by parent tag value
  virtual Tt push(Tt, Tt) = 0;

  // empty(tag)
  // has default methed
  // true if need to update value and push down lazy tag
  virtual bool empty(Tt t) { return t == 0; }

  // clear_tag()
  // has default value
  // return cleared tag value
  virtual Tt clear_tag() { return 0; }
};
```

Example by template
```cpp
struct tree_trait : trait::segment_tree_op<ll> {
  int check() { return 1; }
  ll nan() { return 0; }
  ll merge(ll l, ll r) { return l + r; }
  ll upd(ll seg, ll tag, int l, int r) { return seg + tag; }
  ll push(ll cur, ll par) { return cur + par; }
};

segment_tree<ll, tree_trait> tree(N);
```
## [Geometry](/cpp/geometry.cpp)

## [Vector Deque](/cpp/vec_deque.cpp)
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
