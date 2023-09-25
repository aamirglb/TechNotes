extern crate iron;
#[macro_use]extern crate mime;

extern crate router;
use iron::request;
use router::Router;

use iron::prelude::*;
use iron::status;

extern crate urlencoded;
use std::str::FromStr;
use urlencoded::UrlEncodedBody;

fn post_gcd(request: &mut Request) -> IronResult<Response> {
    let mut response = Response::new();

    let form_data = match request.get_ref::<UrlEncodedBody>() {
        Err(e) => {
            response.set_mut(status::BadRequest);
        }
    }
}
fn main() {
    println!("Serving on http://localhost:4343");
    let mut router = Router::new();

    router.get("/", get_form, "root");
    router.post("/gcd", post_gcd, "gcd");

    Iron::new(router).http("localhost:4343").unwrap();
}

fn get_from(_request: &mut Request) -> IronResult<Response> {
    let mut response = Response::new();

    response.set_mut(status::Ok);
    response.set_mut(mime!(Text/Html; Charset=Utf8));
    response.set_mut(r#"
    <title>GCD Calculator</title>
    <form action="/gcd" method="post">
    <input type="text" name="n" />
    <input type="text" name="n" />
    <button type="submit">Compute GCD</button>
    </form>
    "#);

    Ok(response)
}