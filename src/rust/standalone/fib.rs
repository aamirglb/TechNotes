// Generate fibonacci number

use std::io;
use std::{thread, time};

fn main() {
    let mut limit = String::new();

    println!("Please enter the limit to generate fibonacci number: ");

    io::stdin()
        .read_line(&mut limit)
        .expect("Failed to read line");

    let limit:i32 = limit
        .trim()
        .parse()
        .expect("Invalid number");

    if limit > 2 {
        let mut n1: u64 = 0;
        let mut n2: u64 = 1; 
        println!("{:02}. {} {:0x}", 1, n1, n1);
        println!("{:02}. {} {:0x}", 2, n2, n2);
        let wait_time = time::Duration::from_millis(250);

        for i in 2..limit {
            let n = n1 + n2;
            println!("{:02}. {} {:0x}", i+1, n, n);
            thread::sleep(wait_time);
            n1 = n2;
            n2 = n;
        }
    }
    println!("");
}
