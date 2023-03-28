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
