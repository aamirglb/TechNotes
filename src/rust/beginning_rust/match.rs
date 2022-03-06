fn divide(numerator: f64, denominator: f64) -> Result<f64, String> {
    if denominator == 0. {
        Err(format!("Divide by zero"))
    } else {
        Ok(numerator / denominator)
    }
}

fn main() {
    let mut v = vec![11, 2, 33];

    for _ in 0..5 {
        let item: Option<i32> = v.pop();
        match item {
            Some(number) => print!("{}, ", number),
            None => print!("#, "),
        }
    }

    println!("");
    println!("{:?}, {:?}", divide(8., 2.), divide(8., 0.));

    // let r = divide(8., 2.);
    let r = divide(8., 0.);
    match r {
        Ok(value) => println!("{}", value),
        Err(s) => println!("{}", s),
    }
}