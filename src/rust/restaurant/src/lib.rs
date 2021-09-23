#[cfg(test)]
mod front_of_house {
    pub mod hosting {
        fn add_to_waitlist() {
            println!("front_of_house::hosting::add_to_waitlist()");
        }

        fn seat_at_table() {
            println!("front_of_house::hosting::seat_at_table()");
        }
    }

    mod serving {
        fn take_order() {
            println!("front_of_house::serving::take_order()");
        }

        fn serve_order() {
            println!("front_of_house::serving::serve_order()");
        }

        fn take_payment() {
            println!("front_of_house::serving::take_payment()");
        }
    }
}
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }


pub fn eat_at_restaurant() {
    // Absolute path
    crate::front_of_house::hosting::add_to_waitlist();

    // Relative path
    front_of_house::hosting::add_to_waitlist();
}
