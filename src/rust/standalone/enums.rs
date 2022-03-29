fn main() {
    let _some_number = Some(5);
    let _some_string = Some("a string");
    let _absent_number: Option<i32> = None;

    let x: i8 = 5;
    let y: Option<i8> = Some(14);

//    let _sum = x + y;

    match y {
        Some(y) => println!("y = {}", y),
        None => println!("y is None"),
    }
}
