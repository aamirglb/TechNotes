fn main() {
    enum Continent {
        Europe,
        Asia,
        Africa,
        America,
        Antartica,
    }

    let c: Continent = Continent::Asia;

    match c {
        Continent::Europe => println!("E"),
        Continent::Asia => println!("As"),
        Continent::Africa => println!("Af"),
        Continent::America => println!("Am"),
        Continent::Antartica => println!("An"),
    }

    enum CardinalPoint { North, South, East, West };
    let direction = CardinalPoint::South;
    // if direction == CardinalPoint::South {}

    match direction {
        CardinalPoint::North => println!("N"),
        CardinalPoint::South => println!("S"),
        _ => {},
    }

    // match expression
    println!("** {}", match direction {
        CardinalPoint::North => 'N',
        CardinalPoint::South => 'S',
        _ => '*',
    });

    match "value" {
        "val" => println!("value "),
        _ => println!("other "),
    }

    enum Result {
        Success(f64),
        Failure(u16, char),
        Uncertainty,
    }

    // let outcome = Result::Success(23.67);
    let outcome = Result::Failure(1200, 'X');

    match outcome {
        Result::Success(v) =>
            println!("Result: {}", v),
        Result::Failure(err_code, module) =>
            println!("Error n. {} in module {}",
                err_code, module),
        Result::Uncertainty => {}
    }

    for n in -2..5 {
        println!("{} is {}.", n, match n {
            0 => "zero",
            1 => "one",
            _ if n < 0 => "negative", // Use of Guard
            _ => "plural",
        });
    }
}