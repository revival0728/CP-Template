# Rust CP Template Notice
---

## my_io.rs

1. you have to pass `to_{type}` function to each read function
2. you have to add `else { todo!() }` after calling macro `*read_items!(to_{type})`

### Example

```rust
fn main() {
  let T = read_item!(to_i32);
  
  for _ in 0..T {
    let [N, Q] = *read_items!(to_i32) else { todo!() };
    let V = read_vec!(to_i32);
    ...
  }
}

```

## buffer_io.rs

1. you have to create object `BufferIO` first
2. the `BufferIO::new()` requires one boolean argument, it determines wether to use buffer output or not

### Example
```rust
fn  main() {
  let IO = BufferIO::new();
  let T: i32 = IO.read_item();
  
  for _ in 0..T {
    let [N, Q]: [i32] = IO.read_vec()[..] else { todo!() };
    let V: Vec<i32> = IO.read_vec();
    ...
    let ANS: Vec<i32> = calc_ans();
    let ANS_s1: i32 = calc_ans_s1();
    let ANS_s2: i32 = calc_ans_s2();
    
    IO.println(&ANS[..]);
    IO.println(&[ANS_s1, ANS_s2]);
    // or you can use fprint!()
  }
}
```
