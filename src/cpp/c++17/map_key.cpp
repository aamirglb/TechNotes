#include <iostream>
#include <map>

template <typename M>
void print(const M& m) {
    std::cout << "Race placement: \n";
    for(const auto& [placement, driver] : m) {
        std::cout << placement << ": " << driver << '\n';
    }
}

int main() {
    std::map<int, std::string> race_placement {
        {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
        {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
        {7, "Toad"}, {8, "Donkey Kong Jr."}
    };
    print(race_placement);
    {
        auto a {race_placement.extract(3)};
        auto b {race_placement.extract(8)};
        std::swap(a.key(), b.key());
        race_placement.insert(std::move(a));
        race_placement.insert(std::move(b));
    }
    print(race_placement);
}