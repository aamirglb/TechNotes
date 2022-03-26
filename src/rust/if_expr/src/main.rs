use rand::Rng;

pub enum Protection {
    // Secure { version: u64 },
    Secure(SecureVersion),
    #[deprecated = "using secure mode everywhere is strongly recommended"]
    #[allow(deprecated)]
    Insecure,
}

#[derive(Debug)]
pub enum SecureVersion {
    V1,
    V2,
    V2_1,
}

fn process(prot: Protection) {
    match prot {
        Protection::Secure(version) => {
            println!("Protection is secure thanks to {:?}", version);
        }
        #[allow(deprecated)]
        Protection::Insecure => {
            println!("!! Protection is Insecure !!");
        }
    }
}

fn main() {
    let num = rand::thread_rng().gen_range(0..=10);
    let msg = match num {
//    let msg = match rand::thread_rng().gen_range(0..=10) {
        // match only 10
        10 => "Overwhelming victory".to_string(),
        // match anything 5 or above
        5.. => format!("Victory: {}", num),
        // match anything else (fallback case)
        _ => format!("Defeat: {}", num),
    };
    println!("{}", msg);

    process(Protection::Insecure);
    // process(Protection::Secure{ version: 2 })
    process(Protection::Secure(SecureVersion::V2_1))
}
