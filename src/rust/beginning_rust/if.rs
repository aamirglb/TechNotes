fn main() {
    let n = 1004;
    print!("{}",
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

    let mut i: i32 = 1;

    // while true {
    loop {
        let ii = i * i;
        if ii >= 200 { break; }
        print!("{} ", ii);
        i+=1;
    }
    print!("\n");

    for i in 1..11 {
        print!("{}, ", i*i);
    }

    // let x = ["a"];
    // let _y = x[1];

    // print!("After panic");

    let mut x = [4.; 1000];
    print!("\n{} ", x.len());
}