pub mod modular {  // Modular struct for prime modulus
  #![allow(unused_attributes)]
  #![allow(dead_code)]
  #![feature(generic_const_exprs)]

  use std::{cmp::{Ordering, PartialEq, PartialOrd}, ops, iter::{DoubleEndedIterator, Iterator}, str::FromStr};
  type C = i64;

  mod inner {
    use super::C;

    pub fn fpow(a: C, b: C, m: C) -> C {
      let mut ret: C = 1;
      let mut a = a;
      let mut b = b;
      while b > 0 {
        if b & 1 == 1 {
          ret = ret * a % m;
        }
        a = a * a % m;
        b >>= 1;
      }
      ret
    }
    pub fn rev(a: C, m: C) -> C { fpow(a, m - 2, m) }
  }

  #[derive(Debug, PartialEq, Eq)]
  pub struct ParseModularErr;

  #[derive(Debug, Copy, Clone)]
  pub struct Modular<const M: C> {
    num: i64,
  }

  pub fn make_modular<const M: C, T>(value: T) -> Modular<M> where C: From<T> { Modular::new(value) }
  pub const fn make_const_modular<const M: C, const V: C>() -> Modular<M> { Modular::new_const::<V>() }
  pub const fn mod0<const M: C>() -> Modular<M> { make_const_modular::<M, 0>() }
  pub const fn mod1<const M: C>() -> Modular<M> { make_const_modular::<M, 1>() }
  pub const fn mod2<const M: C>() -> Modular<M> { make_const_modular::<M, 2>() }
  pub const fn mod_max<const M: C>() -> Modular<M> { make_const_modular::<M, -1>() }
  pub const fn mod_min<const M: C>() -> Modular<M> { make_const_modular::<M, 0>() }

  impl<const M: C> Modular<M> {
    pub fn new<T>(num: T) -> Self where T: TryInto<C> {
      let num: C = match num.try_into() { Ok(v) => v, Err(_) => panic!("Modular Init Err!") };
      let num = num % M;
      let num = if num < 0 { num + M } else { num };

      Modular { num }
    }
    pub const fn new_const<const V: C>() -> Self { 
      let num: C = if V % M < 0 { V % M + M } else { V % M };
      Modular { num }
    }
  }

  impl<const M: C> Default for Modular<M> {
    fn default() -> Self {
      Modular::new(0)
    }
  }

  impl<const M: C> ops::Neg for Modular<M> {
    type Output = Modular<M>;
    fn neg(self) -> Self::Output {
      Modular::new(-self.num)
    }
  }
  impl<const M: C> ops::Not for Modular<M> {
    type Output = Modular<M>;
    fn not(self) -> Self::Output {
      Modular::new(!self.num)
    }
  }

  impl<const M: C> ops::Add<Modular<M>> for Modular<M> {
    type Output = Modular<M>;
    fn add(self, rhs: Modular<M>) -> Modular<M> {
      Modular::new(self.num + rhs.num)
    }
  }
  impl<const M: C> ops::AddAssign<Modular<M>> for Modular<M> {
    fn add_assign(&mut self, rhs: Modular<M>) {
      *self = *self + rhs
    }
  }
  impl<const M: C> ops::Div<Modular<M>> for Modular<M> {
    type Output = Modular<M>;
    fn div(self, rhs: Modular<M>) -> Modular<M> {
      Modular::new(self.num * inner::rev(rhs.num, M))
    }
  }
  impl<const M: C> ops::DivAssign<Modular<M>> for Modular<M> {
    fn div_assign(&mut self, rhs: Modular<M>) {
      *self = *self / rhs
    }
  }
  impl<const M: C> ops::Sub<Modular<M>> for Modular<M> {
    type Output = Modular<M>;
    fn sub(self, rhs: Modular<M>) -> Modular<M> {
      Modular::new(self.num - rhs.num)
    }
  }
  impl<const M: C> ops::SubAssign<Modular<M>> for Modular<M> {
    fn sub_assign(&mut self, rhs: Modular<M>) {
      *self = *self - rhs
    }
  }
  impl<const M: C> ops::Mul<Modular<M>> for Modular<M> {
    type Output = Modular<M>;
    fn mul(self, rhs: Modular<M>) -> Modular<M> {
      Modular::new(self.num * rhs.num)
    }
  }
  impl<const M: C> ops::MulAssign<Modular<M>> for Modular<M> {
    fn mul_assign(&mut self, rhs: Modular<M>) {
      *self = *self * rhs
    }
  }

  impl<const M: C> ToString for Modular<M> {
    fn to_string(&self) -> String {
      self.num.to_string()
    }
  }
  impl<const M: C> FromStr for Modular<M> {
    type Err = ParseModularErr;
    fn from_str(s: &str) -> Result<Self, Self::Err> {
      Ok(Self::new(s.parse::<C>().unwrap()))
    }
  }

  impl<const M: C> PartialEq<Modular<M>> for Modular<M> {
    fn eq(&self, other: &Modular<M>) -> bool {
      self.num == other.num
    }
    fn ne(&self, other: &Modular<M>) -> bool {
      self.num != other.num
    }
  }
  impl<const M: C> PartialOrd<Modular<M>> for Modular<M> {
    fn partial_cmp(&self, other: &Modular<M>) -> Option<Ordering> {
      if self.num < other.num { Some(Ordering::Less) }
      else if self.num > other.num { Some(Ordering::Greater) }
      else { Some(Ordering::Equal) }
    }
  }

  // convert to origin types
  impl<const M: C> Modular<M> {
    pub fn to_i32(&self) -> i32 { self.num.try_into().unwrap() }
    pub fn to_i64(&self) -> i64 { self.num }
    pub fn to_u32(&self) -> u32 { self.num.try_into().unwrap() }
    pub fn to_u64(&self) -> u64 { self.num.try_into().unwrap() }
    pub fn to_usize(&self) -> usize { self.num.try_into().unwrap() }
  }


  // implement "for loop" for Modular
  pub struct ModularRange<const M: C> {
    start: Modular<M>,
    end: Modular<M>,
  }

  impl<const M: C> ModularRange<M> {
    pub fn new(start: Modular<M>, end: Modular<M>) -> Self {
      ModularRange { start, end }
    }
  }

  impl<const M: C> Iterator for ModularRange<M> {
    type Item = Modular<M>;
    fn next(&mut self) -> Option<Self::Item> {
      if self.start < self.end {
        let prev_start = self.start;
        self.start += mod1();
        Some(prev_start)
      } else {
        None
      }
    }
  }
  impl<const M: C> DoubleEndedIterator for ModularRange<M> {
    fn next_back(&mut self) -> Option<Self::Item> {
      if self.start < self.end {
        self.end -= mod1();
        Some(self.end)
      } else {
        None
      }
    }
  }

  impl<const M: C> Modular<M> {
    pub fn into_range(&self, end: Modular<M>) -> ModularRange<M> {
      ModularRange::new(*self, end)
    }
  }
  pub fn mod_range<const M: C>(start: Modular<M>, end: Modular<M>) -> ModularRange<M> {
    ModularRange::new(start, end)
  }
}