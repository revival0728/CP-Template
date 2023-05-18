#ifndef NDARRAY_HPP
#define NDARRAY_HPP

#include <array>
#include <cassert>
#include <utility>
#include <iostream>

namespace cp_template {

template<class T, unsigned int D> class ndarray {
  using uint = unsigned int;

  private:
  uint *strides;
  uint *nsize;
  uint data_len;
  T *data;

  protected:
  class view {
    private:
    uint ND;
    uint *strides;
    uint *nsize;
    T *NP;
    
    public:
    view(uint _ND, T *_NP, uint *_strides, uint *_nsize) : ND(_ND), NP(_NP), strides(_strides), nsize(_nsize) {}
    ~view() {}
    view operator[](const uint index) { return view(ND + 1, NP + index * strides[ND], strides, nsize); }
    view at(const uint index) {
      assert(index < nsize[ND]);
      assert(ND + 1 < D);
      return view(ND + 1, NP + strides[ND]);
    }
    T& operator=(const T value) { *NP = value; return *NP; }
    operator T() { return *NP; }
  };
  private:
  void copy(const ndarray<T, D>& other) {
    nsize = other.nsize;
    strides = other.strides;
    data_len = other.data_len;

    delete [] data;
    data = new T[data_len];
    for(uint i = 0; i < data_len; ++i) data[i] = other.data[i];
  }
  template<class _T> void init(const std::array<_T, D>& _nsize, const T DV) {
    strides = new uint[D];
    nsize = new uint[D];
    for(uint i = 0; i < D; ++i) nsize[i] = (uint)(_nsize[i]);
    data_len = 1;
    for(uint i = 0; i < D; ++i) {
      strides[D - i - 1] = data_len;
      data_len *= nsize[i];
    }
    data = new T[data_len];
    for(uint i = 0; i < data_len; ++i) data[i] = DV;
  }

  public:
  ndarray(const std::array<uint, D> _nsize, const T DV = T()) { init(_nsize, DV); }
  ~ndarray() { delete [] data; }
  ndarray<T, D>(const ndarray<T, D>& other) { copy(other); }
  ndarray<T, D>& operator=(const ndarray<T, D>& other) { copy(other); return *this; }
  void swap(ndarray& other) {
    std::swap(data, other.data);
    std::swap(strides, other.strides);
    std::swap(data_len, data_len);
    std::swap(nsize, other.nsize);
  }
  view operator[](const uint index) { return view(0, data, strides, nsize)[index]; }
  view at(const uint index) { return view(0, data, strides, nsize).at(index); }
};

}

#endif
