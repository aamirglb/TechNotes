// use std::cmp::Ordering;
// use std::io;
// use rand::prelude::*;
//
// // use rand::Rng;
//
// fn main() {
//     println!("Guess The Number Game");
//     println!("Please enter your guess:");
//
//     // let mut life = 3;
//     let mut chances = 0;
//     let mut rng = thread_rng();
//     let secret_number = rng.gen_range(1..101);
//     println!("The secret number is: {}", secret_number);
//
//     // while life > 0 {
//     loop {
//         // life -= 1;
//         chances += 1;
//
//         let mut guess = String::new();
//         io::stdin().read_line(&mut guess)
//             .expect("Failed to read line");
//
//         let guess: u32 = match guess.trim().parse() {
//             Ok(num) => num,
//             Err(_) => continue,
//         };
//             // .expect("Please enter a number!!");
//
//         println!("You guessed: {}", guess);
//
//         match guess.cmp(&secret_number) {
//             Ordering::Less => println!("Too small!"),
//             Ordering::Greater => println!("Too big!!"),
//             Ordering::Equal => { println!("You win!!"); break; },
//         }
//     }
//
//     // if life == 0 {
//     //     println!("Sorry!! You lost the game.");
//     // }
//     println!("You completed the game in {} chances", chances);
//
//     println!("{}", ownership_example());
//
//     let o = String::from("hello ownership");
//     let test = o.clone();
//     takes_ownership(o);
//     let x = 5;
//     makes_copy(x);
//
//     println!("The length of '{}' is {}.", test, calculate_len(&test));
//
//     println!("First word index: {}", first_word_v1(&test));
//
//     let mut s2 = String::from("hello");
//     let mut slice = &s2[..];
//     s2.push_str(" , World");
//     println!("Now slice is: {}", slice);
// }
//
// fn ownership_example() -> String
// {
//     let mut s = String::new();
//     // s = "hello".to_string();
//     s.push_str("Hello, ");
//     s.push_str("World!! ");
//     println!("Enter another string");
//
//     let mut ss = String::new();
//     std::io::stdin().read_line(&mut ss);
//     s.push_str(&ss.to_string());
//     s
// }
//
// fn takes_ownership(ss: String) {
//     println!("From takes_ownership: {}!!", ss);
// }
//
// fn makes_copy(si: i32) {
//     println!("From makes_copy: {}!!", si);
// }
//
// fn calculate_len(s: &String) -> usize {
//     s.len()
// }
//
// fn first_word_v1(s: &String) -> usize {
//     let bytes = s.as_bytes();
//
//     for (i, &ch) in bytes.iter().enumerate() {
//         if ch == b' ' {
//             return i;
//         }
//     }
//     s.len()
// }

#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
}

enum IpAddr {
    // V4(String),
    V4(u8, u8, u8, u8),
    V6(String),
}

enum Message {
    Quit,
    Move{x: i32, y: i32 },
    Write(String),
    ChangeColor(i32, i32, i32),
}

impl Message {
    fn call(&self) {
        println!("Calling enum method...");
    }
}

#[derive(Debug)]
enum UsState {
	Alabama,
	Alaska,
	Arizona,
	Arkansas,
	California,
	Colorado,
	Connecticut,
	Delaware,
	Florida,
	Georgia,
	Hawaii,
	Idaho,
	Illinois,
	Indiana,
	Iowa,
	Kansas,
	Kentucky,
	Louisiana,
	Maine,
	Maryland,
	Massachusetts,
	Michigan,
	Minnesota,
	Mississippi,
	Missouri,
	Montana,
	Nebraska,
	Nevada,
	NewHampshire,
	NewJersey,
	NewMexico,
	NewYork,
	NorthCarolina,
	NorthDakota,
	Ohio,
	Oklahoma,
	Oregon,
	Pennsylvania,
	RhodeIsland,
	SouthCarolina,
	SouthDakota,
	Tennessee,
	Texas,
	Utah,
	Vermont,
	Virginia,
	Washington,
	WestVirginia,
	Wisconsin,
	Wyoming,
}
	
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

fn value_in_cents(coin: Coin) -> u8 {
    let mut count = 0;
    match coin {
        Coin::Penny => {
            println!("Found a Penny!");
            count += 1;
            1
        },
        Coin::Nickel => {
            println!("Found a Nickel!");
            count += 1;
            5
        }
        Coin::Dime => { count += 1; 10 },
        Coin::Quarter(state) => {
            println!("State quarter from {:?}!", state);
            25
        }
    }
}

fn main() {
    let rect1 = Rectangle { width: 30, height: 50 };

    println!("rect1 is {:?}", rect1);
    println!("The area of the rectangle is {} square pixels.", rect1.area() /*area(&rect1)*/);

    let mut rect2: Rectangle = Rectangle { width: 0, height: 0};
    rect2.width = 10;
    rect2.height = 5;
    println!("rect2 is {:#?}", rect2);
    println!("The area of the rectangle is {} square pixels.", rect2.area() /*area(&rect2)*/);

    // let home = IpAddr::V4(String::from("127.0.0.1"));
    let home = IpAddr::V4(127, 0, 0, 1);
    let loopback = IpAddr::V6(String::from("::1"));

    let m = Message::Write(String::from("hello"));
    m.call();

    let some_num = Some(5);
    let some_str = Some("a some string");
    let no_num: Option<i32> = None;

    println!("{:#?}, {:#?}", some_num, some_str);

    let x: i8 = 5;
    let y: Option<i8> = Some(5);
    let sum = x + match y { Some(value) => value, None => 0 };
    println!("Sum is = {}", sum);

    println!("Value in cents = {}", value_in_cents(Coin::Penny));
    println!("Value in cents = {}", value_in_cents(Coin::Quarter(UsState::Alaska)));
    println!("Value in cents = {}", value_in_cents(Coin::Quarter(UsState::California)));
    // println!("Count = {}", count);
    // for state in UsState {
    //     println!("Us State {:#?}", state);
    // }
    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);
    if let Some(six) = Some(6) {
        println!("Some(six) is 6");
    }
}

fn area(rectangle: &Rectangle) -> u32 {
    rectangle.width * rectangle.height
}

fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i + 1),
    }
}

