/*
 *
 * Vector Dequeue
 * Author: revival0728
 *
 * Some function Tested, unstable
 *
 */


#include <bits/stdc++.h>
using namespace std;


namespace cp_template {

template<class T> class vec_deque {
  using iterator = typename vector<T>::iterator;

  private:
  int capacity;
  iterator pl, pr;
  vector<T> deq;

  public:
  vec_deque(int _capacity) : capacity(_capacity) { 
    deq.resize(capacity << 1 | 1);
    pl = deq.begin() + capacity;
    pr = deq.begin() + capacity;
  }
  template<class P> void push_back(P val) { *pr++ = val; }
  template<class P> void push_front(P val) { *pl-- = val; }
  template<class ...P> void emplace_back(P ...t) { *pr++ = T(t...); }
  template<class ...P> void emplace_front(P ...t) { *pl-- = T(t...); }
  size_t size() { return pr - pl; }
  void pop_back() { --pr; assert(size() >= 0 && "cannot pop empty vec_deque"); }
  void pop_front() { ++pl; assert(size() >= 0 && "cannot pop empty vec_deque"); }
  bool empty() { return size() == 0; }
  T& operator[](const size_t i) { return deq[i]; }
  T& front() { return *pl; }
  T& back() { return *pr; }
  iterator begin() { return pl; }
  iterator end() { return pr; }
};

}


int main() {}