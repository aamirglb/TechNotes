fn main() {
    print!("The sum is {}\n", 80.3 + 34.9);
    println!("{}", "These
        are
            thress lines");
    println!("{}", "These \
        is \
        just one line");

    let number;
    number = 15;
    println!("{}", number);

    println!("{} {}", str::len("abcde"), "abcdef".len());
    
    let n = 4;
    println!("{}",
             if n > 1000 {
                 "big"
             }
             else if n > 0 {
                 "small"
             }
             else if n < 0 {
                 "negative"
             } 
             else {
                 "neither positive nor negative"
             }
        );

    let mut i = 0;
    while i < 50 {
        i += 1;
        if i % 3 == 0 { continue; }
        if i * i > 400 { break; }
        print!("{} ", i * i);
    }
    println!("");

    let mut limit = 4;

    // limit is evaluated at the begining of the loopo only
    for i in 1..limit {
        limit -= 1;
        print!("{} ", i);
    }
    print!(":{}\n", limit);

    let x = ["a"];
//    let _y = x[1];

    let mut fib = [1; 20]; // array of 20 int initialize with 1

    for i in 2..fib.len() {
        fib[i] = fib[i - 2] + fib[i - 1];
    }

    for i in 0..fib.len() {
        print!("{} ", fib[i]);
    }
    println!("");
    
    let mut x = vec!["This", "is"];
    println!("{} {}. Length: {}", x[0], x[1], x.len());
    x.push("a");
    x.push("sentence");

    for i in 0..x.len() {
        print!(" {} ", x[i]);
    }
    println!("");

    let _a = [""; 0];  // empty array of string
    let _b = vec![true; 0];

    println!("{:?} {:?}", [1, 2, 3], vec![4, 5]);
    
    //for i in 0..256 {
    //    println!("{}: [{}]", i, i as u8 as char);
    //}
}
