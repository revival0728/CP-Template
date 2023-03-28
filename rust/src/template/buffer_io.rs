#![allow(dead_code)]
#![allow(unused_macros)]
#![allow(unused_macros)]
#![allow(non_snake_case)]
#![allow(unused_imports)]
#![allow(unused_variables)]

use std::io;

struct BufferIO {
    buffer: String,
    stdin: io::Stdin,
    stdout: io::Stdout,
}

impl BufferIO {
    
    pub fn new() -> Self {
        let buffer = String::new();
        let stdin = io::stdin();
        let stdout = io::stdout();

        BufferIO { buffer, stdin, stdout }
    }

    pub fn read<T>(&mut self) -> T where T::TryFrom<&str>, {
        if self.buffer == "" {
            match self.stdin.read_line(&mut self.buffer) {
                Ok(_) => {},
                Err(_) => { assert!(false) },
            }
        }
        match self.buffer.strip_prefix(" ") {
            Some(s) => { self.buffer = String::from(s) },
            None => {}
        };
        let first_space = match self.buffer.find(" ") {
            Some(id) => { id },
            None => { self.buffer.len() }
        };
        let res = T::try_from(self.buffer[0..first_space]);

        return res;
    }
}
