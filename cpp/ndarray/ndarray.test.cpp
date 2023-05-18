#include <iostream>
#include "ndarray.hpp"
using namespace cp_template;

int main() {
  int n = 2, m = 2;
  ndarray<int, 2> ar({n, m}, 0);
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      ar[i][j] = i + j;
    }
  }
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      std::cout << ar[i][j] << ' ';
    }
    std::cout << '\n';
  }
}