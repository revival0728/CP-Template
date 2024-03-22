/*
 *
 * The Fenwick Tree template
 * Author: revival0728
 *
 * Test with: https://judge.yosupo.jp/problem/predecessor_problem
 * Status: AC
 * Time: 824ms
 * Memory: 55.77Mib
 * 
 */

#include <bits/stdc++.h>

namespace cp_template {
  #include <vector>
  #define lowbit(x) ((x)&(-x))

  // 1-base
  template<class T, class trait> class fenwick_tree {
    int size;
    std::vector<T> bit;
    trait op;

    public:
    fenwick_tree(int _size) : size(_size + 1), op(trait()) {
      bit.resize(size, T());
    }
    void build(const std::vector<T>& arr) {
      assert(arr.size() == bit.size() - 1);
      for(int i = 1; i < size; ++i)
        bit[i] = arr[i - 1];
      for(int i = 1; i < size; ++i) {
        int j = lowbit(i);
        if(j < size)
          bit[j] = op.merge(bit[j], bit[i]);
      }
    }
    void upd(int x, T v) {
      assert(1 <= x && x < size);
      for(; x < size; x += lowbit(x))
        bit[x] = op.merge(bit[x], v);
    }
    T sum(int x) {
      assert(0 <= x && x < size);
      T ret = 0;
      for(; x; x -= lowbit(x))
        ret = op.merge(ret, bit[x]);
      return ret;
    }
    T qry(int l, int r) { //[l, r]
      --l;
      assert(l <= r);
      return op.sub(sum(l), sum(r));
    }
  };
  #undef lowbit

  namespace trait {
    template<class T> struct fenwick_tree_op {
      // merge(l, r)
      // merge values of [l] and [r] or bit array and update value
      virtual T merge(const T&, const T&) = 0;

      // sub(l, r)
      // subtract values of [1, l) and [1, r] => become [l, r]
      virtual T sub(const T&, const T&) = 0;
    };

    template<class T> struct fenwick_tree_add : public fenwick_tree_op<T> {
      T merge(const T& l, const T& r) { return l + r; }
      T sub(const T& l, const T& r) { return r - l; };
    };
    template<class T> struct fenwick_tree_xor : public fenwick_tree_op<T> {
      T merge(const T& l, const T& r) { return l ^ r; }
      T sub(const T& l, const T& r) { return r ^ l; };
    };
  }
}

using namespace cp_template;
using namespace std;

int main() {
  cin.tie(0), ios_base::sync_with_stdio(0);

  int N, Q;
  string T;

  cin >> N >> Q >> T;

  fenwick_tree<int, trait::fenwick_tree_add<int>> tree(N);
  
  function<int(int, function<bool(int, int)>)> search = [&](int tar, function<bool(int, int)> cmp) {
    int l = 1, r = N + 1;
    int m = (l + r) / 2;

    while(l < r) {
      if(cmp(tree.qry(1, m), tree.qry(1, tar)))
        l = m + 1;
      else
        r = m;
      m = (l + r) / 2;
    }
    
    return m;
  };

  for(int i = 0; i < N; ++i)
    if(T[i] == '1')
      tree.upd(i + 1, 1);

  const function<void(int)> operations[] = {
    [&](int k) {
      if(!tree.qry(k, k))
        tree.upd(k, 1);
    },
    [&](int k) {
      if(tree.qry(k, k))
        tree.upd(k, -1);
    },
    [&](int k) {
      cout << tree.qry(k, k) << '\n';
    },
    [&](int k) {
      int res = search(k - 1, [&](int a, int b) { return a <= b; });
      cout << (res == N + 1 ? -1 : res - 1) << '\n';
    },
    [&](int k) {
      int res = search(k, [&](int a, int b) { return a < b; });
      cout << (tree.qry(1, res) == 0 ? -1 : res - 1) << '\n';
    }
  };

  while(Q--) {
    int c, k;
    cin >> c >> k, ++k;
    operations[c](k);
  }
}