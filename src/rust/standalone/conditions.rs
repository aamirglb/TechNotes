fn main() {
    let condition = true;
    let number = if condition { 5 } else { 6 };
    println!("The value of number is: {}", number);

    let condition = false;
    let number = if condition { 5 } else { 6 };
    println!("The value of number is: {}", number);

    let mut count = 0;
    'counting_up: loop {
        println!("count = {}", count);
        let mut remaining = 10;

        loop {
            println!("remaining = {}", remaining);
            if remaining == 9 {
                break;
            }
            if count == 2 {
                break 'counting_up;
            }
            remaining -= 1;
        }
        count += 1;
    }
    println!("End count = {}", count);

    let mut counter = 0;
    let result = loop {
        counter += 1;
        if counter == 10 {
            break counter * 2;
        }
    };
    println!("The result is: {}", result);

    let a = [10, 20, 30, 40, 50];
    for ele in a {
        println!("The value is: {}", ele);
    }

    for number in (1..5).rev() {
        println!("{}", number);
    }
    println!("LIFTOFF!!");
}
