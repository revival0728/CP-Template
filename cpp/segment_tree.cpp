/*
 *
 * The Segment Tree template
 * Author: revival0728
 *
 * Tested with: https://atcoder.jp/contests/abc138/tasks/abc138_d
 * Status: AC
 * Time: 303ms
 * Memory: 38388 KB
 *
 */

#include <bits/stdc++.h>

namespace cp_template {
  #include <vector>
  #include <limits>
  #define mid ((l + r) / 2)
  #define lc (id << 1)
  #define rc (id << 1 | 1)

  template<class T, class trait, class Tt = T> class segment_tree {
    int size, rb, check;
    T nan;
    Tt clear_tag;
    std::vector<T> seg;
    std::vector<Tt> tag;
    trait op;

    void push(int id, int l, int r) {
      if(op.empty(tag[id])) return;
      seg[id] = op.upd(seg[id], tag[id], l, r);
      if(l != r) {
        tag[lc] = op.push(tag[lc], tag[id]);
        tag[rc] = op.push(tag[rc], tag[id]);
      }
      tag[id] = clear_tag;
    }
    void build(const std::vector<T>& arr, int id, int l, int r) {
      if(l == r) {
        seg[id] = arr[id - 1];
        return;
      }
      build(arr, lc, l, mid), build(arr, rc, mid + 1, r);
      seg[id] = op.merge(seg[lc], seg[rc]);
    }
    void upd(int id, int l, int r, int ql, int qr, const Tt& v) {
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
      if(r < ql || l > qr) return nan;
      if(ql <= l && r <= qr) return seg[id];
      return op.merge(qry(lc, l, mid, ql, qr), qry(rc, mid + 1, r, ql, qr));
    }

    public:
    segment_tree(int _size) : rb(_size), size(_size << 2 | 1), op(trait()), nan(op.nan()), check(op.check()), clear_tag(op.clear_tag()) {
      seg.resize(size, T());
      tag.resize(size, clear_tag);
    }
    void build(const std::vector<T>& arr) {
      assert(arr.size() == (size >> 2));
      build(arr, 1, 1, rb);
    }
    void upd(int x, Tt v) {
      assert(1 <= x && x <= rb && check == 0);
      upd(1, 1, rb, x, x, v);
    }
    void upd(int ql, int qr, Tt v) {
      assert(1 <= ql && ql <= qr && qr <= rb && check == 1);
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
  }
}
