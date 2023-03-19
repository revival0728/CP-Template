#![allow(dead_code)]
#![allow(unused_macros)]

use std::io;


// Begin of my_io.rs

fn to_string(item: &str) -> String { String::from(item) }
fn to_u32(item: &str) -> u32 { item.parse::<u32>().unwrap() }
fn to_u64(item: &str) -> u64 { item.parse::<u64>().unwrap() }
fn to_i32(item: &str) -> i32 { item.parse::<i32>().unwrap() }
fn to_i64(item: &str) -> i64 { item.parse::<i64>().unwrap() }
fn to_f32(item: &str) -> f32 { item.parse::<f32>().unwrap() }
fn to_f64(item: &str) -> f64 { item.parse::<f64>().unwrap() }
fn to_bool(item: &str) -> bool { item.parse::<bool>().unwrap() }

fn read_item<T>(trans: fn(&str) -> T) -> T {
    let mut buf = String::new();

    io::stdin().read_line(&mut buf).expect("In read_item():: Type Error");

    return trans(&buf.trim())
}

fn read_vec<T>(trans: fn(&str) -> T) -> Vec<T> {
    let mut buf = String::new();

    io::stdin().read_line(&mut buf).expect("In read_items():: Type Error");
    
    let items: Vec<&str> = buf.trim().split(' ').collect();
    let mut ret: Vec<T> = vec![];

    for &it in items.iter() {
        ret.push(trans(&it.trim()))
    }

    return ret
}

macro_rules! read_item  { ($trans: ident) => { read_item($trans) }; }
macro_rules! read_items { ($trans: ident) => { &read_vec($trans)[..] }; }
macro_rules! read_vec   { ($trans: ident) => { read_vec($trans)}; }

// End of my_io.rs

fn main() {}

