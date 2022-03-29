fn main() {
    let mut s = String::from("Hello, World!");
    let word = first_word(&s);
    println!("word: {}", word); 
    
    println!("{}", &s[..5]);
    s.clear();
    println!("word: {}", word); 
}

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for(i, &item) in bytes.iter().enumerate() {
        if item == b' ' {
            return &s[..i];
        }
    }
    &s[..]
}

fn first_word_v1(s: &String) -> usize {
    let bytes = s.as_bytes();

    for(i, &item) in bytes.iter().enumerate() {
        println!("({}, {})", i, item as char); 
        if item == b' ' {
            return i;
        }
    }
    s.len()
}

