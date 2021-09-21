fn main() {
    let s1 = String::from("hello");

    let (s2, len) = calculate_length(s1);

    println!("The length of '{}' is {}.", s2, len);

    let s3 = String::from("Rust");
    let len2 = calculate_length_v2(&s3);

    println!("The length of '{}' is {}.", s3, len2);

    change(&s3);
}

fn calculate_length(s: String) -> (String, usize) {
    let length = s.len();
    (s, length)
}

fn calculate_length_v2(s: &String) -> usize {
    s.len()
}

fn change(some_str: &String) {
    some_str.push_str(", world");
}