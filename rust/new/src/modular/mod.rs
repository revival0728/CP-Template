pub mod modular;

#[cfg(test)]
mod test_modular {
  use std::str::FromStr;

  use super::modular::modular::{make_const_modular, make_modular, Modular, mod_range};
  const M: i64 = (1e9 + 7.0) as i64;
  type Mod = Modular<M>;

  const MOD0: Mod = make_const_modular::<M, 0>();
  const MOD1: Mod = make_const_modular::<M, 1>();
  const MOD2: Mod = make_const_modular::<M, 2>();
  const MOD4: Mod = make_const_modular::<M, 4>();
  const MOD_M_1: Mod = make_const_modular::<M, {M - 1}>();
  const MOD_1: Mod = make_const_modular::<M, -1>();

  #[test]
  fn init() {
    let a = Mod::new(10);
    let b = Mod::new(M + 10);
    let c: Mod = make_modular(0);
    let d: Mod = Default::default();
    let _ = [MOD0; 5];

    assert_eq!(a, b);
    assert_eq!(c, d);
    assert_eq!(MOD_M_1, MOD_1);
  }

  #[test]
  fn add() {
    let mut e = MOD0;
    e += MOD2;
    assert_eq!(e, MOD2);
    assert_eq!(MOD1 + MOD_1, MOD0);
    assert_eq!(MOD2 + MOD_1, MOD1);
  }
  #[test]
  fn sub() {
    let mut e = MOD0;
    e -= MOD1;
    assert_eq!(e, MOD_1);
    assert_eq!(MOD0 - MOD1, MOD_M_1);
    assert_eq!(MOD2 - MOD1, MOD1);
  }
  #[test]
  fn mul() {
    let mut e = MOD2;
    e *= MOD2;
    assert_eq!(e, MOD4);
    assert_eq!(MOD2 * MOD_1, make_modular(1000000005));
  }
  #[test]
  fn div() {
    let mut e = MOD2;
    e /= MOD2;
    assert_eq!(e, MOD1);
    assert_eq!(MOD4 / MOD2, MOD2);
  }
  #[test]
  fn comp() {
    assert!(MOD2 < MOD4);
    assert!(MOD_1 > MOD4);
    assert!(MOD2 <= MOD2);
  }
  #[test]
  fn string_stuff() {
    let e = Mod::from_str("1").unwrap();
    let f = "2".parse::<Mod>().unwrap();
    assert_eq!(e, MOD1);
    assert_eq!(f, MOD2);
    assert_eq!(MOD1.to_string(), "1");
  }
  #[test]
  fn not_neg() {
    assert_eq!(-MOD1, MOD_1);
    assert_eq!(!MOD1, make_modular(-2));
  }
  #[test]
  fn utility() {
    for (m, i) in MOD1.into_range(MOD4).zip(1..4) {
      assert_eq!(m.to_i32(), i);
    }
    for (m, i) in MOD1.into_range(MOD4).rev().zip((1..4).rev()) {
      assert_eq!(m.to_i32(), i);
    }
    for (m, i) in mod_range(MOD1, MOD4).zip(1..4) {
      assert_eq!(m.to_i32(), i);
    }
  }
}