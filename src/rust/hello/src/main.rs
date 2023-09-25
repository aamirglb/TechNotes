use std::io::Write;
use std::str::FromStr;

fn main() {
    let mut nums = Vec::new();
    for arg in std::env::args().skip(1) {
        let n = u64::from_str(&arg);
        match n {
            Ok(v) => nums.push(v),
            Err(e) => { println!("Error parsing input {:?}", e) },
        };

        // nums.push(u64::from_str(&arg)
        // .expect("error parsing arguments"));
    }

    if nums.len() == 0 {
        writeln!(std::io::stderr(), "Usage: gcd NUMBER").unwrap();
        std::process::exit(1);
    }
    let mut d = nums[0];
    for m in &nums[1..] {
        d = gcd(d, *m);
    }
    println!("gcd of {:?} is {}", nums, d);

    // println!("{}", gcd(40, 16));
    // println!("{}", gcd(0, 8));

    let mut n = Vec::new();
    for i in 1..(u64::MAX / 10000 ) {
        n.push(i);
    }
    for i in 0..n.len() {
        print!("{} ", n[i]);
    }

}

// compute GCD using Euclid's algorithm
fn gcd(mut n: u64, mut m: u64) -> u64 {
    assert!( n!=0 && m!=0);

    while m!= 0 {
        if m < n {
            let t = m;
            m = n;
            n = t;
        }
        m = m % n;
    }
    n
}

#[test]
fn test_gcd() {
    assert_eq!(gcd(14, 15), 1);
    assert_eq!(gcd(2*3*11, 17*3*19*11), 3*11);
}

#[test]
fn test_gcd2() {
    assert_eq!(gcd(4, 2), 3);
}