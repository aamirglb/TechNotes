fn print_double(mut x: f64) {
    x *= 2.;
    println!("{}", x);
}

enum E {
    E1,
    E2,
}

fn f1() -> E {
    E::E1
}

fn f2<T>(ch: char, n1: T, n2: T) -> T {
    if ch == 'a' { n1 }
    else { n2 }
}

fn double_negative(mut a: [i32; 10]) -> [i32; 10] {
    for i in 0..10 {
        if a[i] < 0 { a[i] *= 2; }
    }
    a
}

fn f3(p: &f64) {
    let a = Box::new(*p);
    {
        let b = Box::new([1, 2, 3]);
        println!("{} {:?}", *a, *b);
    }
    let c = Box::new(true);
    println!("{} {}", a, c);
}

fn main() {
    let x = 4.;
    print_double(x);
    println!(" {} ", x);

    println!("{}", match f1() { E::E1 => 1, _ => 0});

    let mut arr = [9, -5, 2, -7, 3, 4, -1, 0, 6, -4];
    arr = double_negative(arr);
    println!("{:?}", arr);

    let a = 15;
    let ref_a = &a;
    println!("{} {} {}", a, *ref_a, ref_a);

    let mut b = 10;
    let mut p = &mut b;
    println!("{}", p);
    *p = 20;
    println!("{}", p);

    let a: i16 = f2::<i16>('a', 37, 41);
    let b: f64 = f2::<f64>('b', 37.2, 41.1);
    println!("{} {}", a, b);

    f3(&3.4);
}