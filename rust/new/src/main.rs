mod modular;
mod cpio;

use cpio::cpio::*;

fn main() {
  let s = read_str!().unwrap();
  let t = read_str!().unwrap();
  let a = read!(usize).unwrap();
  let (b, c) = read!(i32, i32).unwrap();
  let v = read_vec!(i32).unwrap();

  println!("{}", s);
  println!("{}", t);
  println!("{} {} {}", a, b, c);
  println!("{}", vec_join_space(&v));
}
