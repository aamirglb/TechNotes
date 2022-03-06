fn main() {
    for c in 0..255 {
        // println!("{}: [{}]", c, c as u8 as char);
    }

    let a: () = ();
    let b = {12; 87; 283};
    let c = {12; 87; 283; };
    let d = {};
    let e = if false {};
    let f = while false {};

    println!("{:?} {:?} {:?} {:?} {:?} {:?} ", a, b, c, d, e, f);
}