#include <optional>
#include <string>
#include <iostream>

std::optional<int> asInt(const std::string& s) {
    std::optional<int> ret;
    try {
        // return std::stoi(s);
        ret = std::stoi(s);
    }
    catch(...) {
        // return std::nullopt;
    }
    return ret;
}

int main() {
    for(auto s : {"42", "  077", "hello", "0x33"}) {
        std::optional<int> oi = asInt(s);
        // if(oi) {
        if(oi.has_value()) {
            std::cout << "convert '" << s << "' to int: " << *oi << "\n";
        } else {
            std::cout << "can't convert '" << s << "' to int\n";
        }
    }
}