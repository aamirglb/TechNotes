use std::collections::{HashMap, HashSet};

fn main() {
    let available = HashMap::from_iter([(2, "b"), (3, "c"), (4, "d")]);
    let mut set = HashSet::new();
    
    for i in [1, 2, 3, 4, 5] {
        match available.get(&i) {
            Some(s) => set.insert(*s),
            None => ()
        }
    }
}