// Formula
// C = (F - 32) / 1.80
fn main() {

    println!("Enter temperature in fahrenheit");

    // let mut input_str = String::new();
    
    // std::io::stdin().read_line(&mut input_str)
    //     .expect("Failed to read line");

    // let fahrenheit: f64 = input_str.trim().parse::<f64>().unwrap(); // {
    // //     Ok(num) => num,
    // //     Err(_) => println!("Invalid number"),
    // // };
    
    // let celsius = (fahrenheit - 32.0) / 1.8;

    // println!("{} celsius temperature {}", fahrenheit, celsius);

    println!("Fahrenheit\tCelsius");
    println!("-------------------");
    for num in (0..14) {
        let f = (num as f64 * 10.) + 32.0;
        let c = convert_f_to_c(f);
        println!("{}\t{:.2}", f, c);
    }
}

fn convert_f_to_c(f: f64) -> f64 {
    (f - 32.0) / 1.8
}
