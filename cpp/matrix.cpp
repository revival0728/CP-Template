#include <vector>
#include <cassert>

namespace cp_template
{
  // init a matrix
  // Matrix<int> I{{1, 0}, {0, 1}}
  template<class T> using Matrix = std::vector<std::vector<T>>;
  template<class T> void set_matrix(Matrix<T>& m, int x, int y, T v) {
    m = Matrix<T>(x, std::vector<T>(y, v));
  }
  template<class T> Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) {
    assert(a[0].size() == b.size());
    int sa = a.size(), sb = b[0].size(), sc = a[0].size();
    Matrix<T> ret; set_matrix(ret, sa, sb, 0);
    for(int i = 0; i < sa; ++i) {
      for(int j = 0; j < sb; ++j) {
        for(int k = 0; k < sc; ++k) {
          ret[i][j] += a[i][k] * b[k][j];
          // add ret[i][j] %= MOD if needed
        }
      }
    }
    return ret;
  }
}

#include <iostream>
using namespace std;
using namespace cp_template;

using Mat = Matrix<int>;

int main() {
  Mat a{{1, 1}, {2, 3}}, b{{1, 1}, {1, 1}};
  Mat c = a * b;
  for(int i = 0; i < 2; ++i) {
    for(int j = 0; j < 2; ++j) {
      cout << c[i][j] << ' ';
    }
    cout << '\n';
  }
}