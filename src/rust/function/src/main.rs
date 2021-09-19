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