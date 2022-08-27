#include <iostream>
#include <functional>
#include <list>
#include <map>
#include <unordered_map>

struct billinoaire {
    std::string name;
    double dollars;
    std::string country;
};

int main() {
    std::list<billinoaire> billionaires {
        {"Bill Gates", 86.0, "USA"},
        {"Warren Buffet", 75.6, "USA"},
        {"Jeff Bezos", 72.8, "USA"},
        {"Amancio Ortega", 71.3, "Spain"},
        {"Mark Zuckerberg", 56.0, "USA"},
        {"Carlos Slim", 54.5, "Mexico"},
        {"Bernard Arnault", 41.5, "France"},
        {"Liliane Bettencourt", 39.5, "France"},
        {"Wang Jianlin", 31.3, "China"},
        {"Li Ka-shing", 31.2, "Hong Kong"},
    };

    // std::map<std::string, std::pair<const billinoaire, size_t>> m;
    std::unordered_map<std::string, std::pair<const billinoaire, size_t>> m;

    for(const auto& b: billionaires) {
        auto [itr, success] = m.try_emplace(b.country, b, 1);
        if(!success) {
            m[b.country].second += 1;
            // itr->second.second += 1;
        }
    }

    for(const auto& [key, value] : m) {
        const auto &[b, count] = value;
        std::cout << b.country << " : " << count << " billionaires.\n";
        std::cout << "Richest is " << b.name << " with " << b.dollars << " B$\n\n";
    }
}