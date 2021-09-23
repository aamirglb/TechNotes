fn main() {
    println!("Hello, world!");

    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);

    for i in 0..10 {
        match i {
            1 => println!("one"),
            3 => println!("three"),
            5 => println!("five"),
            7 => println!("seven"),
            _ => println!("x",),
        }
    }
}

fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i+1),
    }
}