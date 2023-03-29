#![allow(dead_code)]
#![allow(unused_macros)]
#![allow(unused_macros)]
#![allow(non_snake_case)]
#![allow(unused_imports)]
#![allow(unused_variables)]

mod template;

use std::io;
use std::collections::HashMap;
use std::collections::HashSet;
use crate::template::buffer_io::BufferIO;

macro_rules! to_usize { ($num: ident) => { usize::try_from($num).unwrap() } }

fn main() {
    let mut IO = BufferIO::new(true);

    let a: i32 = IO.read_item();
    let b: Vec<i32> = IO.read_vec();
    let [c, d]: [i32] = IO.read_vec()[..] else { todo!() };

    fprintln!(IO, "a = {}, b = {}, c = {}", a, c, d);
    // println!("a = {}, c = {}, d = {}", a, c, d);
    IO.println(&b[..]);
    IO.println(&[a, c, d]);
    IO.println(&["OK"]);
    IO.write("OK\n");
}

