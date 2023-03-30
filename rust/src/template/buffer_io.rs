#![allow(dead_code)]
#![allow(unused_macros)]
#![allow(unused_macros)]
#![allow(non_snake_case)]
#![allow(unused_imports)]
#![allow(unused_variables)]

use std::io;
use std::io::Write;
use std::fmt;
use std::str::FromStr;
use std::convert::Into;

pub struct BufferIO {
    buffer: String,
    out: String,
    stdin: io::Stdin,
    stdout: io::Stdout,
    use_out_buffer: bool,
}

#[macro_export]
macro_rules! fprint {
    ($IO: ident, $fmt: expr) => { $IO.write(format!($fmt)) };
    ($IO: ident, $fmt: expr, $($args: tt)*) => { $IO.write(format!($fmt, $($args)*)) };
}

#[macro_export]
macro_rules! fprintln {
    ($IO: ident, $fmt: expr) => { $IO.out(format!($fmt)); $IO.write("\n") };
    ($IO: ident, $fmt: expr, $($args: tt)*) => { $IO.out(format!($fmt, $($args)*)); $IO.write("\n") };
}

impl Drop for BufferIO {
    fn drop(&mut self) {
        if self.use_out_buffer {
            self.release_out();
        }
    }
}

impl BufferIO {
    
    pub fn new(use_out_buffer: bool) -> Self {
        let buffer = String::new();
        let stdin = io::stdin();
        let stdout = io::stdout();
        let out = "".to_string();

        BufferIO { buffer, stdin, stdout, out, use_out_buffer }
    }

    // check is buffer empty, if true, then read stdin to buffer
    fn ensure_buffer(&mut self) {
        if self.buffer.len() == 0 {
            match self.stdin.read_line(&mut self.buffer) {
                Ok(_) => {},
                Err(_) => { panic!("cannot read stdin to buffer") }
            }
        }
        self.buffer = self.buffer.trim().to_string();
    }

    fn ensure_out(&mut self) {
        if !self.use_out_buffer {
            self.release_out();
        }
    }

    fn release_out(&mut self) {
        match self.stdout.write_all(self.out.as_bytes()) {
            Ok(_) => {},
            Err(_) => { panic!("cannout write out buffer to stdout") }
        }
        self.out.clear();
    }

    pub fn read_item<T>(&mut self) -> T where T: FromStr {
        self.ensure_buffer();

        let first_space_id: usize = match self.buffer.find(" ") {
            Some(id) => { id },
            None => { self.buffer.len() } }; let origin_val: &str = &self.buffer[0 .. first_space_id];
        let res: T = match origin_val.parse() {
            Ok(val) => { val },
            Err(_) => { panic!("type convertion on the item went wrong") }
        };
        if first_space_id == self.buffer.len() {
            self.buffer.clear();
        } else {
            self.buffer = self.buffer[first_space_id + 1 .. ].to_string();
        }

        return res;
    }

    pub fn read_items<T>(&mut self, quantity: usize) -> Vec<T> where T: FromStr {
        let mut res: Vec<T> = Vec::new();

        for _ in 0..quantity { res.push(self.read_item()) }

        return res;
    }

    pub fn read_vec<T>(&mut self) -> Vec<T> where T: FromStr {
        self.ensure_buffer();

        let v: Vec<&str> = self.buffer.split(' ').collect();
        let res = v.iter().map(| e | { match e.parse::<T>() { Ok(r) => { r }, Err(_) => { panic!("type convertion on the item went wrong") } } }).collect();
        self.buffer.clear();

        return res;
    }

    pub fn print<T>(&mut self, items: &[T]) where T: ToString + Copy {
        for (id, item) in items.iter().enumerate() {
            self.out.push_str((*item).to_string().as_str());
            self.out.push_str( if id == items.len() - 1 { "" } else { " " } );
        }
        self.ensure_out();
    }

    pub fn println<T>(&mut self, items: &[T]) where T: ToString + Copy {
        self.print(items);
        self.out.push_str("\n");
        self.ensure_out();
    }

    pub fn out(&mut self, s: String) {
        self.out += s.as_str();
        self.ensure_out();
    }

    pub fn write(&mut self, s: &str) {
        self.out += s;
        self.ensure_out();
    }
}
