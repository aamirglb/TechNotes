fn main() {
    let mut s = String::from("hello");
    s.push_str(", world!!");

//    let s2 = s;
    println!("{}", s);

    takes_ownership(s);

    let x = 4;
    makes_copy(x);

    let s1 = gives_ownership();
    println!("s1: {}", s1);

    let s2 = String::from("hello");
    let s3 = takes_and_gives_back(s2);
    println!("s3: {}", s3);

    let mut s1 = String::from("hello");
    let len = calculate_length(&s1);
    println!("The length of '{}' is {}.", s1, len);

    change(&mut s1);
    println!("s1: {}", s1);
}

fn takes_ownership(some_string: String) {
    println!("{}", some_string);
}

fn makes_copy(some_integer: i32) {
    println!("{}", some_integer);
}

fn gives_ownership() -> String {
    String::from("gives_ownership")
}

fn takes_and_gives_back(a_string: String) -> String {
    a_string
}

fn calculate_length(s: &String) -> usize {
    s.len()
}

fn change(some_string: &mut String) {
    some_string.push_str(", world!!");
}
