fn main() {
    let mut fib =[1; 30];
    for i in 2..fib.len() {
        fib[i] = fib[i-2] + fib[i-1];
    }

    // for i in 0..fib.len() {
    //     print!("{:02}. {}\n", i+1, fib[i]);
    // }

    let x = vec![1, 2, 3];
    print!("{:?}", x);
}

