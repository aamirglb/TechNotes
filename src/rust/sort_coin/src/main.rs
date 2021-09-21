#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska,
    Arizona,
    Arkansas,
    California,
    Colorado,
    Connecticu,
    Delaware,
    Florida,
    Georgia,
    Hawaii,
    Idaho,
    Illinois,
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState),
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => { 
            println!("Lucky penny!");
            1
        },
        Coin::Nickel => 5,
        Coin::Dime => 10, 
        Coin::Quarter(state) => {
            println!("State quarter from {:?}!", state);
            25
        },
    }
}

fn main() {
    println!("Hello, world!");

    println!("{}", value_in_cents(Coin::Quarter(UsState::Alaska)));
    println!("{}",value_in_cents(Coin::Dime));
    println!("{}",value_in_cents(Coin::Nickel));
    println!("{}",value_in_cents(Coin::Penny));
}
