use std::io;

fn main() {
    let a = [1, 2, 3, 4, 5];

    println!("Please enter an array index.");

    let mut index = String::new();

    io::stdin()
        .read_line(&mut index)
        .expect("Failed to read line");

    let index: usize = index
        .trim()
        .parse()
        .expect("Index entered was not a number");

    let element = a[index];

    println!("The value of element at index {} is: {}",
             index, element);

    function_test();

    let x = plus_one(5);
    println!("The value of x is: {}", x);
}

fn function_test() {
    let y = {
        let x = 3;
        x + 1
    };

    println!("The value of y is {}", y);
}

fn plus_one(x: i32) -> i32 {
    x + 1
}
