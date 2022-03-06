fn main() {
    let mut x = vec!["This", "is", "a", "sentense"];
    x.insert(1, "line");
    x.insert(2, "contains");
    println!("{:?}", x);

    x.remove(3);
    x.push("about Rust");
    x.pop();

    for i in 0..x.len() {
        print!("{} ", x[i]);
    }

    let one_thousand = 1e3;
    let one_million = 1e6;
    let thirteen_billions_and_half = 13.5e9;
    let twelve_millionths = 12e-6;

    println!("{}, {}, {}, {}", one_thousand, one_million, thirteen_billions_and_half, twelve_millionths);

    let arr = [11, 22, 33];
    let i: usize = 2;
    // let i: u32 = 2;
    println!("{}", arr[i]);

    let c: char = 'a';
    println!("{}", '\u{20AC}');

}