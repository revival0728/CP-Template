pub mod bitset {
  #![allow(unused_attributes)]
  #![allow(dead_code)]
  #![feature(generic_const_exprs)]

  use std::{clone::Clone, fmt::Debug, ops};

  mod inner {
    pub const fn bitset_size<const B: usize>() -> usize {
      B / 64 + if B % 64 == 0 { 0 } else { 1 }
    }
  }

  #[derive(Clone, Debug, Default)]
  pub struct BitSet<const B: usize> {
    bits: Vec<u64>
  }

  impl<const B: usize> BitSet<B> {
    pub fn new() -> Self {
      let bits: Vec<u64> = vec![Default::default(); inner::bitset_size::<B>()];

      BitSet { bits }
    }
    pub fn size() -> usize { inner::bitset_size::<B>() }
    pub fn len() -> usize { B }

    pub fn set(&mut self, i: usize) {
      assert!(i < B);
      self.bits[i / 64] |= 1 << (i % 64);
    }
    pub fn reset(&mut self, i: usize) {
      assert!(i < B);
      self.bits[i / 64] &= !(1 << (i % 64));
    }
    pub fn fill(&mut self) {
      for i in 0..inner::bitset_size::<B>() {
        self.bits[i] = u64::MAX;
      }
    }
    pub fn clear(&mut self) {
      for i in 0..inner::bitset_size::<B>() {
        self.bits[i] = 0;
      }
    }
    pub fn flip(&mut self, i: usize) {
      self.bits[i / 64] ^= 1 << (i % 64);
    }
    pub fn rotate(&mut self) {
      for i in 0..inner::bitset_size::<B>() {
        self.bits[i] = !self.bits[i];
      }
    }
  }

  impl<const B: usize> ops::BitAndAssign for BitSet<B> {
    fn bitand_assign(&mut self, rhs: Self) {
      for i in 0..inner::bitset_size::<B>() {
        self.bits[i] &= rhs.bits[i];
      }
    }
  }
  impl<const B: usize> ops::BitAnd for BitSet<B> {
    type Output = Self;
    
    fn bitand(self, rhs: Self) -> Self::Output {
      let mut ret = self.clone();
      ret &= rhs;
      ret
    }
  }
  impl<const B: usize> ops::BitOrAssign for BitSet<B> {
    fn bitor_assign(&mut self, rhs: Self) {
      for i in 0..inner::bitset_size::<B>() {
        self.bits[i] |= rhs.bits[i];
      }
    }
  }
  impl<const B: usize> ops::BitOr for BitSet<B> {
    type Output = Self;
    
    fn bitor(self, rhs: Self) -> Self::Output {
      let mut ret = self.clone();
      ret |= rhs;
      ret
    }
  }
  impl<const B: usize> ops::BitXorAssign for BitSet<B> {
    fn bitxor_assign(&mut self, rhs: Self) {
      for i in 0..inner::bitset_size::<B>() {
        self.bits[i] ^= rhs.bits[i];
      }
    }
  }
  impl<const B: usize> ops::BitXor for BitSet<B> {
    type Output = Self;
    
    fn bitxor(self, rhs: Self) -> Self::Output {
      let mut ret = self.clone();
      ret ^= rhs;
      ret
    }
  }
  impl<const B: usize> ops::Not for BitSet<B> {
    type Output = Self;

    fn not(self) -> Self::Output {
      let mut bits = vec![0_u64; inner::bitset_size::<B>()];
      for i in 0..inner::bitset_size::<B>() {
        bits[i] = !self.bits[i];
      }
      Self { bits }
    }
  }
  impl<const B: usize> ops::ShlAssign<usize> for BitSet<B> {
    fn shl_assign(&mut self, rhs: usize) {
      let gap = rhs / 64;
      let shift = rhs % 64;
      let mut mask = 0_u64;
      if gap >= 1 {
        for i in (gap..inner::bitset_size::<B>()).rev() {
          self.bits[i] = self.bits[i - gap];
          self.bits[i - gap] = 0;
        }
      }
      for i in 0..inner::bitset_size::<B>() {
        let overflow = self.bits[i] >> (64 - shift);
        self.bits[i] <<= shift;
        self.bits[i] |= mask;
        mask = overflow;
      }
    }
  }
  impl<const B: usize> ops::Shl<usize> for BitSet<B> {
    type Output = Self;

    fn shl(self, rhs: usize) -> Self::Output {
      let mut ret = self.clone();
      ret <<= rhs;
      ret
    }
  }
}