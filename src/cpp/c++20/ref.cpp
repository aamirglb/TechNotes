#include <iostream>
#include <string>
#include <charconv>

void separateOddsAndEvens(const int arr[],
        size_t size,
        int*& odds,
        size_t& numOdds,
        int*& evens,
        size_t& numEvens)
{
    numOdds = numEvens = 0;
    for(size_t i {}; i < size; ++i) {
        if(arr[i] % 2 == 1) {
            ++numOdds;
        } else {
            ++numEvens;
        }
    }
    odds = new int[numOdds];
    evens = new int[numEvens];

    size_t oddsPos {}, evensPos {};
    for(size_t i {}; i < size; ++i) {
        if(arr[i] % 2 == 1) {
            odds[oddsPos++] = arr[i];
        } else {
            evens[evensPos++] = arr[i];
        }
    }
}

const std::string message { "Test Message"};
const std::string& foo() { return message; }

int main() {
    int unSplit [] {1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 4, 7, 5};
    int* odds, *evens;
    size_t numOdds, numEvens;

    separateOddsAndEvens(unSplit, std::size(unSplit),
        odds,
        numOdds,
        evens,
        numEvens);

    for(size_t i{}; i < numOdds; ++i) {
        std::cout << odds[i] << ", ";
    }
    std::cout << std::endl;

    for(size_t i{}; i < numEvens; ++i) {
        std::cout << evens[i] << ", ";
    }
    std::cout << std::endl;

    auto f1 { foo() };
    std::cout << f1 << std::endl;
    f1 += " update";
    std::cout << f1 << std::endl;

    auto c { 11 };
    // auto d { 11, 22};

    const std::string toParse{"  123USD"};
    size_t idx {};
    int value { std::stoi(toParse, &idx) };
    std::cout << "\nParsed value: " << value << std::endl;
    std::cout << "first no-parsed char: " << toParse[idx] << std::endl;

    const size_t sz{50};
    std::string out(sz, ' ');
    auto [ptr, err] {std::to_chars(out.data(), out.data() + out.size(), 123456)};
    if(err == std::errc{}) {
        std::cout << out << std::endl;
    }

    // out.clear();

    auto [ptr1, err1] { std::to_chars(out.data(),
                                    out.data() + out.size(),
                                    3.14256,
                                    std::chars_format::fixed,
                                    10)};
    if(err1 == std::errc{}) {
        std::cout << out << std::endl;
    } else {
        std::cout << "conversion failed: " << out.size() << std::endl;
    }

{
    // perfect round-tripping demo
    double value1 {0.314826};
    // std::string out(sz, ' ');
    // auto [ptr, err] { std::to_chars(out.data(), out.data() + out.size(), value1)};
    // if(err == std::errc{}) {
    //     std::cout << out << std::endl;
    // }

    std::string out{"0.314826"};
    double value2{};
    auto [ptr1, err1] { std::from_chars(out.data(), out.data() + out.size(), value2)};
    if(err1 == std::errc{}) {
        if(value1 == value2) {
            std::cout << "perfect roundtrip\n";
        } else {
            std::cout << "no perfect roundtrip?\n";
        }
    }
}
}