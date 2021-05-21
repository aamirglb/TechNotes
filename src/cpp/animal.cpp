#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

struct Animal {
    std::string name;
    int32_t     legs;
    bool        has_tail;

    Animal(std::string n, int32_t l, bool t) :
        name{n}, legs{l}, has_tail{t}
    {}

    bool operator<(const Animal* other) const {
        std::cout << "< called\n";
        return legs < other->legs;
    }

    friend std::ostream& operator<<(std::ostream &out, const Animal& a) {
        out << a.name << ", " << a.legs << ", " << std::boolalpha << a.has_tail << '\n';
        return out;
    }
};

int main() {
    std::vector<Animal *> v;
    v.push_back(new Animal("cat", 4, true));
    v.push_back(new Animal("cow", 4, true));
    v.push_back(new Animal("crow", 2, false));
    v.push_back(new Animal("fish", 0, false));

    std::sort(v.begin(), v.end(), [](const auto *a1, const auto *a2) -> bool {return a1->legs < a2->legs;});
    for(const auto e: v) {
        std::cout << *e;
    }

    // std::set<Animal *> s;
    // s.insert(new Animal("cat", 4, true));
    // s.insert(new Animal("cow", 4, true));
    // s.insert(new Animal("crow", 2, false));
    // for(const auto e: s) {
    //     std::cout << *e;
    // }
}