fn main() {
    let mut x: i32 = 5;
    println!("the value of x is: {}", x);
    let x = x + 1;
    println!("The value of x now is: {}", x);
    let x = x + 1;
    println!("The value of x now is: {}", x);

    let spaces = "    ";
    let spaces = spaces.len();
    println!("spaces: {}", spaces);

    let mut s = "    ";
    // s = s.len();  // can't mutate type

    // consider giving `guess` a type
    // let guess = "42".parse().expect("Not a number!");

    let mut c: u8 = 0xff;
    // c = c + 1;

    let f = 2.0;
    let f2: f32 = 3.0; // f32

    let tup: (i32, f64, u8) = (500, 6.4, 1);

    let (x, y, z) = tup;
    println!("The value of y is: {}", y);
    println!("x: {}, y: {}, z: {}", tup.0, tup.1, tup.2);

    let a: [i32; 5] = [1, 2, 3, 4, 5];
    let b = [3; 5]; // 5 element initialize with 3
    let idx = 10;
    // println!("a[10]: {}", a[idx]);

    print_num(66);
}

fn print_num(x: i32) {
    println!("The value of x is: {}", x);
}
