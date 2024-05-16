#include <bits/stdc++.h>

namespace cp_template {
  namespace geometry {
    namespace constant {
      #ifndef CP_GEOMETRY_EPS
      #define CP_GEOMETRY_EPS
      constexpr double EPS = 1e-8;
      #endif

      #ifndef CP_GEOMETRY_PI
      #define CP_GEOMETRY_PI
      constexpr double PI = 3.14159265359;
      #endif
    }
    namespace eps_compare {
      #ifndef CP_EPS_COMPARE
      #define CP_EPS_COMPARE
      template<class T> bool eq(T l, T r) { return std::abs(l - r) < constant::EPS; }
      template<class T> bool ne(T l, T r) { return std::abs(l - r) > constant::EPS; }
      template<class T> bool le(T l, T r) { return (l - r) < -constant::EPS; }
      template<class T> bool ge(T l, T r) { return (l - r) > constant::EPS; }
      template<class T> bool leq(T l, T r) { return (l - r) < constant::EPS; }
      template<class T> bool geq(T l, T r) { return (l - r) > -constant::EPS; }
      #endif
    }
  }

  #include <cmath>
  #define sq(x) ((x) * (x))
  template<class T> struct Vector {
    T x, y;
    Vector() : x(0), y(0) {}
    Vector(T _x, T _y) : x(_x), y(_y) {}
    friend Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
      return Vector<T>(a.x + b.x, a.y + b.y);
    }
    friend Vector<T> operator-(const Vector<T>& a, const Vector<T>& b) {
      return Vector<T>(a.x - b.x, a.y - b.y);
    }
    friend Vector<T> operator*(const Vector<T>& a, const T k) {
      return Vector<T>(a.x * k, a.y * k);
    }
    friend Vector<T> operator/(const Vector<T>& a, const T k) {
      return Vector<T>(a.x / k, a.y / k);
    }
    friend T operator*(const Vector<T>& a, const Vector<T>& b) {
      return a.x * b.x + a.y * b.y;
    }
    friend T operator^(const Vector<T>& a, const Vector<T>& b) {
      return a.x * b.y - a.y * b.x;
    }
    friend bool operator<(const Vector<T>& a, const Vector<T>& b) {
      using geometry::eps_compare::eq;
      using geometry::eps_compare::le;
      return eq(a.x, b.x) ? le(a.y, b.y) : le(a.x, b.x);
    }
    friend bool operator>(const Vector<T>& a, const Vector<T>& b) {
      using geometry::eps_compare::eq;
      using geometry::eps_compare::ge;
      return eq(a.x, b.x) ? ge(a.y, b.y) : ge(a.x, b.x);
    }
    friend bool operator==(const Vector<T>& a, const Vector<T>& b) {
      using geometry::eps_compare::eq;
      return eq(a.x, b.x) && eq(a.y, b.y);
    }
    friend bool operator!=(const Vector<T>& a, const Vector<T>& b) {
      using geometry::eps_compare::ne;
      return ne(a.x, b.x) || ne(a.y, b.y);
    }
    void read() {
      int _x, _y;
      std::cin >> _x >> _y;
      x = _x;
      y = _y;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector<T> v) {
      return os << "{" << v.x << "," << v.y << "}";
    }
    T length() { return std::sqrt(sq(x) + sq(y)); }
    Vector<T> rotate(T angle) {
      return Vector<T>(x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle));
    }
  };
  #undef sq

  namespace geometry {

    #include <vector>
    #include <algorithm>
    template<class T> std::vector<Vector<T>> convex_hull(std::vector<Vector<T>> hull) {
      using eps_compare::leq;
      std::sort(hull.begin(), hull.end());
      std::vector<Vector<T>> stk; stk.reserve(hull.size() * 2);
      int top = 0;
      for(int i = 0; i < hull.size(); ++i) {
        while(top >= 2 && leq((stk[top - 1] - stk[top - 2]) ^ (hull[i] - stk[top - 2]), 0.0))
          stk.pop_back(), --top;
        stk.push_back(hull[i]);
        ++top;
      }
      for(int i = hull.size() - 2, t = top + 1; i >= 0; --i) {
        while(top >= t && leq((stk[top - 1] - stk[top - 2]) ^ (hull[i] - stk[top - 2]), 0.0))
          stk.pop_back(), --top;
        stk.push_back(hull[i]);
        ++top;
      }
      stk.pop_back();
      return stk;
    }

    #include <cmath>
    template<class T> bool banana(const Vector<T>& p1, const Vector<T>& p2, const Vector<T>& q1, const Vector<T>& q2) {
      using eps_compare::eq;
      using eps_compare::ge;
      using eps_compare::le;
      auto in_seg = [&](const Vector<T>& a, const Vector<T>& b, const Vector<T>& m) -> bool {
        Vector<T> ma = m - a, ba = b - a, sum = ma + ba;
        return eq(ma ^ ba, 0) && (ge(std::abs(sum.x), std::abs(ba.x))) && (ge(std::abs(sum.y), std::abs(ba.y)));
      };
      auto scale_down = [&](const T v) -> int { 
        return ge(v, 0) - le(v, 0); 
      };
      auto cross = [&](const Vector<T>& o, const Vector<T>& a, const Vector<T>& b, const Vector<T>& c) -> bool {
        return scale_down((a - o) ^ (b - o)) * scale_down((a - o) ^ (c - o)) <= 0;
      };
      return (in_seg(p1, p2, q1) || in_seg(p1, p2, q2) || in_seg(q1, q2, p1) || in_seg(q1, q2, p2)) ||
             (cross(p1, p2, q1, q2) && cross(q1, q2, p1, p2));
    }
  }
}

int main() {}
