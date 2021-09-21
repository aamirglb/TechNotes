// enum IpAddr {
//     V4(String),
//     V6(String),
// }

// enum IpAddr {
//     V4(u8, u8, u8, u8),
//     V6(String),
// }
// fn main() {
//     // let home = IpAddr::V4(String::from("127.0.0.1"));
//     let home = IpAddr::V4(127, 0, 0, 1);
//     let loopback = IpAddr::V6(String::from("::1"));
// }

enum Message {
    Quit,
    Move{ x: i32, y: i32},
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        println!("call method");
    }
}

fn main() {
    let m = Message::Write(String::from("hello"));
    m.call();

    let some_num = Some(5);
    let some_str = Some("a string");
    let absent_num: Option<i32> = None;

    println!("num: {}, str: {}", some_num, some_str);

    let x: i8 = 5;
    let y: Option<i8> = Some(5);
    let sum = x+y;
}
