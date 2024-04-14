pub mod cpio {
  #![allow(dead_code)]
  #![allow(unused_macros)]
  #![allow(unused_imports)]

  use core::fmt::Debug;
  use std::{collections::VecDeque, io, str::FromStr};

  type InputBuffType = VecDeque<String>;
  static mut INPUT_BUFFER: String = String::new();
  static mut INPUT_DEQ: InputBuffType = InputBuffType::new();
  unsafe fn read_input_buffer() {
    INPUT_BUFFER.clear();
    io::stdin().read_line(&mut INPUT_BUFFER).unwrap();
  }
  unsafe fn ensure_input_deq() {
    if INPUT_DEQ.is_empty() { 
      read_input_buffer();
      INPUT_DEQ = 
      INPUT_BUFFER
        .trim()
        .split_whitespace()
        .map(|x| x.to_string())
        .collect();
    }
  }
  pub unsafe fn read_line_fn() -> Option<String> {
    read_input_buffer();
    if INPUT_BUFFER.is_empty() {
      None
    } else {
      Some(INPUT_BUFFER.trim().to_string())
    }
  }
  pub unsafe fn read_str_fn() -> Option<String> {
    ensure_input_deq();
    INPUT_DEQ.pop_front()
  }
  pub unsafe fn read_fn<T: FromStr>() -> Option<T> where T::Err: Debug {
    if let Some(s) = read_str_fn() {
      Some(s.parse::<T>().unwrap())
    } else {
      None
    }
  }
  pub unsafe fn read_vec_fn<T: FromStr>() -> Option<Vec<T>> where T::Err: Debug {
    if let Some(s) = read_line_fn() {
      Some(
        s
        .split_whitespace()
        .map(|x| x.parse::<T>().unwrap())
        .collect::<Vec<T>>()
      )
    } else {
      None
    }
  }

  pub fn vec_to_string<const SEP: char, T>(arg: &Vec<T>) -> String where T: ToString {
    arg.iter().map(|x| x.to_string()).collect::<Vec<String>>().join(&SEP.to_string())
  }

  pub fn vec_join_space<T>(arg: &Vec<T>) -> String where T: ToString {
    vec_to_string::<' ', T>(arg)
  }

  pub fn vec_join<T>(arg: &Vec<T>) -> String where T: ToString {
    arg.iter().map(|x| x.to_string()).collect::<Vec<String>>().join("")
  }

  macro_rules! read {
    ($t:ty) => {
      unsafe { 
        read_fn::<$t>()
      }
    };
    ($t:ty, $($p:ty)*) => {
      'read_macro: {
        Some((
          match read!($t) {
            Some(x) => x,
            None => break 'read_macro None
          },
          match read!($($p)*) {
            Some(x) => x,
            None => break 'read_macro None
          }
        ))
      }
    };
  }

  macro_rules! read_vec {
    ($t:ty) => {
      unsafe {
        read_vec_fn::<$t>()
      }
    };
  }

  macro_rules! read_str {
    () => {
      unsafe {
        read_str_fn()
      }
    };
  }

  macro_rules! read_line {
      () => {
        unsafe {
          read_line_fn()
        }
      };
  }

  pub(crate) use read;
  pub(crate) use read_vec;
  pub(crate) use read_str;
  pub(crate) use read_line;
}