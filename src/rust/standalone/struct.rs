struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

fn build_user(email: String, username: String) -> User {
    User {
        email: email,
        username: username,
        active: true,
        sign_in_count: 1,
    }
}

fn main() {
    let mut user1 = User {
        email: String::from("aamir@abc.com"),
        username: String::from("aamir"),
        active: true,
        sign_in_count: 1,
    };

    user1.sign_in_count+=1;
    println!("{:?}", user1.sign_in_count);

    let mut user2 = build_user(String::from("xyz@abc.com"), String::from("xyz"));
//    println!("{:?}", user1);
}
