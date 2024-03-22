/*
 *
 * The Segment Tree template
 * Author: revival0728
 *
 * Not Tested
 *
 */

#include <bits/stdc++.h>

namespace cp_template {
  #include <vector>
  #include <limits>
  #define mid ((l + r) / 2)
  #define lc (id << 1)
  #define rc (id << 1 | 1)

  template<class T, class trait, class Tt = int> class segment_tree {
    int size, rb;
    std::vector<T> seg;
    std::vector<Tt> tag;
    trait op;

    void push(int id, int l, int r) {
      if(!op.to_prog(tag[id])) return;
      seg[id] = op.upd(seg[id], tag[id], l, r);
      if(l != r) {
        tag[lc] = op.push(tag[lc], tag[id]);
        tag[rc] = op.push(tag[rc], tag[id]);
      }
      tag[id] = op.clear_tag();
    }
    void build(const std::vector<T>& arr, int id, int l, int r) {
      if(l == r) {
        seg[id] = arr[id - 1];
        return;
      }
      build(arr, lc, l, mid), build(arr, rc, mid + 1, r);
      seg[id] = op.merge(seg[lc], seg[rc]);
    }
    void upd(int id, int l, int r, int ql, int qr, const T& v) {
      push(id, l, r);
      if(r < ql || l > qr) return;
      if(ql <= l && r <= qr) {
        tag[id] = op.push(tag[id], v);
        push(id, l, r);
        return;
      }
      upd(lc, l, mid, ql, qr, v), upd(rc, mid + 1, r, ql, qr, v);
      seg[id] = op.merge(seg[lc], seg[rc]);
    }
    T qry(int id, int l, int r, int ql, int qr) {
      push(id, l, r);
      if(r < ql || l > qr) return op.nan();
      if(ql <= l && r <= qr) 
        return op.merge(qry(lc, l, mid, ql, qr), qry(rc, mid + 1, r, ql, qr));
    }

    public:
    segment_tree(int _size) : rb(_size), size(_size << 2 | 1), op(trait()) {
      seg.resize(size, T());
      tag.resize(size, op.clear_tag());
    }
    void build(const std::vector<T>& arr) {
      assert(arr.size() == (size >> 2));
      build(arr, 1, 1, rb);
    }
    void upd(int x, T v) {
      assert(1 <= x && x <= rb && op.check() == 0);
      upd(1, 1, rb, x, x, v);
    }
    void upd(int ql, int qr, T v) {
      assert(1 <= ql && ql <= qr && qr <= rb && op.check() == 1);
      upd(1, 1, rb, ql, qr, v);
    }
    T qry(int ql, int qr) {
      assert(1 <= ql && ql <= qr && qr <= rb);
      return qry(1, 1, rb, ql, qr);
    }
  };
  #undef mid
  #undef lc
  #undef rc

  namespace trait {
    template<class T, class Tt = int> struct segment_tree_op {
      // nan()
      // return out of boundary value
      virtual constexpr T nan() = 0;

      // merge(l, r)
      // merge values of [l] and [r]
      virtual T merge(const T&, const T&) = 0;

      // check()
      // return segment tree update method
      // 0 -> single update
      // 1 -> range update
      virtual constexpr int check() = 0;

      // methed(seg, value)
      // for single update
      // method for updating seg value
      virtual T method(const T&, T) = 0;

      // weight(l, r)
      // return the weight for tag value
      virtual T weight(int, int) = 0;

      // upd(seg, tag, l, r)
      // has default method
      // update seg value by tag value and interval [l, r]
      virtual T upd(const T& seg, const Tt& tag, int l, int r) {
        return method(seg, (T)(tag) * weight(l, r));
      }

      // push(current_tag, parent_tag)
      // update current tag value by parent tag value
      virtual Tt push(const Tt&, const Tt&) = 0;

      // is_prog(tag)
      // has default methed
      // true if need to update value and push down lazy tag
      virtual bool to_prog(const Tt& t) { return t == 0; }

      // clear_tag()
      // has default value
      // return cleared tag value
      virtual constexpr Tt clear_tag() { return 0; }
    };
    template<class T, class Tt = int> struct segment_tree_single_update : public segment_tree_op<T, Tt> {
      constexpr int check() { return 0; }
    };
    template<class T, class Tt = int> struct segment_tree_range_update : public segment_tree_op<T, Tt> {
      constexpr int check() { return 1; }
    };
    template<class T, class Tt = int> struct segment_tree_update_by_single : public segment_tree_op<T, Tt> {
      virtual T weight(int l, int r) { return 1; }
    };
    template<class T, class Tt = int> struct segment_tree_update_by_range : public segment_tree_op<T, Tt> {
      virtual T weight(int l, int r) { return r - l + 1; }
    };
    template<class T, class Tt = int> struct segment_tree_update_by_set : public segment_tree_op<T, Tt> {
      virtual T method(const T& seg, T v) { return v; }
      virtual Tt push(const Tt& current, const Tt& parent) { return parent; }
    };
    template<class T, class Tt = int> struct segment_tree_update_by_merge : public segment_tree_op<T, Tt> {
      virtual T method(const T& seg, T v) { return merge(seg, v); }
      virtual Tt push(const Tt& current, const Tt& parent) { return merge(current, parent); }
    };
    template<class T, class Tt = int> struct segment_tree_add : public segment_tree_op<T, Tt> {
      constexpr T nan() { return 0; }
      T merge(const T& l, const T& r) { return l + r; }
    };
    template<class T, class Tt = int> struct segment_tree_min : public segment_tree_update_by_single<T, Tt>, segment_tree_update_by_merge<T, Tt> {
      constexpr T nan() { return std::numeric_limits<T>::max(); }
      T merge(const T& l, const T& r) { return min(l, r); }
    };
    template<class T, class Tt = int> struct segment_tree_max : public segment_tree_update_by_single<T, Tt>, segment_tree_update_by_merge<T, Tt> {
      constexpr T nan() { return std::numeric_limits<T>::min(); }
      T merge(const T& l, const T& r) { return max(l, r); }
    };

    namespace segment_tree {
      template<class T, class Tt = int> using single_update = segment_tree_single_update<T, Tt>;
      template<class T, class Tt = int> using range_update = segment_tree_range_update<T, Tt>;
      template<class T, class Tt = int> using update_by_single = segment_tree_update_by_single<T, Tt>;
      template<class T, class Tt = int> using update_by_range = segment_tree_update_by_range<T, Tt>;
      template<class T, class Tt = int> using update_by_set = segment_tree_update_by_set<T, Tt>;
      template<class T, class Tt = int> using update_by_merge = segment_tree_update_by_merge<T, Tt>;
    }
  }
}

using namespace std;
using namespace cp_template;
using namespace trait::segment_tree;

struct tree_trait : public trait::segment_tree_max<int>, range_update<int> {};

int main() {
  segment_tree<int, tree_trait> tree(10);
}