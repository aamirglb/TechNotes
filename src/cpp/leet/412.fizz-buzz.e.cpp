#include <iostream>
#include <string>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

vector<string> fizzBuzz(int n) {
    vector<string> res(n);

    for(int i = 1; i <= n; ++i) {
        if( (i % 3 == 0) && (i % 5 == 0) ) {
            res[i] = "FizzBuzz";
        } else if((i % 3) == 0) {
            res[i] = "Fizz";
        } else if(i%5 == 0) {
            res[i] = "Buzz";
        } else {
            res[i] = to_string(i);
        }
    }
    return res;
}

int main() {
    fmt::print("{}\n", fizzBuzz(3));
    fmt::print("{}\n", fizzBuzz(5));
    fmt::print("{}\n", fizzBuzz(15));

}