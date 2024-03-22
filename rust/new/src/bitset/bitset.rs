pub mod bitset {
  #![allow(unused_attributes)]
  #![allow(dead_code)]
  #![feature(generic_const_exprs)]

  mod inner {
    pub const fn bitset_size<const B: usize>() -> usize {
      B / 64 + if B % 64 == 0 { 0 } else { 1 }
    }
  }
  struct BitSet<const B: usize> {
    bits: Vec<i64>
  }

  impl<const B: usize> BitSet<B> {
    pub fn new() -> Self {
      let bits = vec![0_i64; inner::bitset_size::<B>()];

      BitSet { bits }
    }
  }
}