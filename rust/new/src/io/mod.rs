pub mod io {
  #![allow(dead_code)]
  #![allow(unused_macros)]

  use std::{collections::VecDeque, io};

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

  pub fn vec_to_string<T>(arg: &Vec<T>) -> String where T: ToString {
    arg.iter().map(|x| x.to_string()).collect::<Vec<String>>().join(" ")
  }

  #[macro_export]
  macro_rules! read {
    ($t:ty) => {
      unsafe { 
        ensure_input_deq(); 
        if INPUT_DEQ.is_empty() {
          None
        } else {
          Some(
          INPUT_DEQ
            .pop_front()
            .unwrap()
            .parse::<$t>()
            .unwrap()
          )
        }
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

  #[macro_export]
  macro_rules! read_vec {
    ($t:ty) => {
      unsafe {
        read_input_buffer();
        if INPUT_BUFFER.is_empty() {
          None
        } else {
          Some(
          INPUT_BUFFER
            .trim()
            .split_whitespace()
            .map(|x| x.parse::<$t>().unwrap())
            .collect::<Vec<$t>>()
          )
        }
      }
    };
  }
}