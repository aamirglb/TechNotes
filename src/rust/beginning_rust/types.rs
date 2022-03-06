use std::fmt;

fn main() {
    let data = (100_000_000, 123.45, 'Q');
    let copy_of_data = data;

    println!("{}, {}, {}", data.0, copy_of_data.1, data.2);

    println!("{:?}", copy_of_data);

    struct Data {
        integer: i32,
        fractional: f32,
        character: char,
        five_bytes: [u8; 5],
    }

    impl fmt::Display for Data {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            write!(f, "int : {}\nfrac: {}\nchar: {}\nbyte: {:?}\n",
                self.integer, self.fractional, self.character, self.five_bytes)
            // write!(f, "int : {}\nfrac: {}\nchar: {}\n",
            //     self.0, self.1, self.2)
        }
    }

    let data = Data {
        integer: 10_000_000,
        fractional: 123.45,
        character: 'Q',
        five_bytes: [1, 2, 3, 4, 5],
    };

    println!("{}", data);
}