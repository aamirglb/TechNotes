fn main() {
    let s = String::from("hello world");
    let word = first_word(&s);
    println!("First word in '{}' is '{}'", s, word);

    let s = String::from("Rust Programming Language");
    let word = first_word(&s);
    println!("First word in '{}' is '{}'", s, word);

    let mut s = String::from("Programming");
    let word = first_word(&s);
    {
        s.clear();
    }
    
    println!("First word in '{}' is '{}'", s, word);
}

fn first_word(s: &String) -> &str {
    let bytes = s.as_bytes();

    for (i, &c) in bytes.iter().enumerate() {
        if c == b' ' {
            return &s[..i];
        }
    }
    &s[..]
}
