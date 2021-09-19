use std::io::Write; // <--- bring flush() into scope

fn main() {
    println!("Enter the length of fibonacci sequence");

    let mut len = String::new();

    std::io::stdin().read_line(&mut len)
        .expect("Fail to read input");

    let len: i32 = len.trim().parse().unwrap();

    let mut f0: u64 = 0;
    let mut f1: u64 = 1;
    print!("{} {} ", f0, f1);
    std::io::stdout().flush().unwrap();

    for _i in (3..len+1) {
        let f2: u64 = f0 + f1;
        print!(" {} ", f2);
        std::io::stdout().flush().unwrap();
        f0 = f1;
        f1 = f2;
    }
    println!("");
}
