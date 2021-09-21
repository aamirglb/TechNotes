fn main() {
    let x = 5;

    let y = {
        let x = 3;
        x + 1
    };

    println!("The value of y is: {}", y);

    let z = five();

    println!("The value of z is: {}", z);

    let number = 2;

    if number < 5 {
        println!("true");
    } else {
        println!("false");
    }

    let condition = false;
    let a = if condition {
        5
    } else {
        6
    };

    println!("The value of a is: {}", a);

    let b = loop_ex();
    println!("The value of b is: {}", b);

    let a = [10, 20, 30, 40, 50];

    for ele in a.iter() {
        println!("the value is: {}", ele);
    }

    for num in (1..5).rev() {
        println!("{}...", num);
    }

    let s = String::from("hello");
    take_ownership(s);
    // println!("take_ownership: {}", s);

    let mut ss1 = gives_ownership();

    let ss2 = takes_and_gives_back(&mut ss1);
    println!("ss2: {}", ss2);
}


fn five() -> i32 {
    5
}

fn loop_ex() -> i32 {
    let mut counter = 0;
    let result = loop {
        counter += 1;

        if counter == 10 {
            break counter * 2;
        }
    };
    result
}

fn take_ownership(s: String) {
    println!("take_ownership: {}", s);
}

fn gives_ownership() -> String {
    let mut some_str = String::from("hello");
    some_str
}

fn takes_and_gives_back(&mut a_str: String) -> String {
    a_str.push_str(", world!!");
    a_str
}