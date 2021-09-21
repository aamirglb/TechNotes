struct User {
    username: String,
    email: String,
    sign_in_count: u64,
    active: bool,
}

fn main() {
    let user1 = User {
        email: String::from("aamir@test.com"),
        username: String::from("Aamir"),
        active: true,
        sign_in_count: 1,
    };

    println!("{}, {}, {}, {}", user1.username, user1.email, user1.active, user1.sign_in_count);

    let user2 = build_user(String::from("ali@ali.com"), String::from("Ali"));
    println!("{}, {}, {}, {}", user2.username, user2.email, user2.active, user2.sign_in_count);

    let user3 = User {
        email: String::from("md@example.com"),
        username: String::from("Mohammad"),
        ..user1
    };
    println!("{}, {}, {}, {}", user3.username, user3.email, user3.active, user3.sign_in_count);

    struct Color(i32, i32, i32);
    struct Point(i32, i32, i32);

    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);
}

fn build_user(email: String, username: String) -> User {
    User {
        email: email,
        username: username,
        active: true,
        sign_in_count: 1,
    }
}