#include <iostream>
#include <format>
#include <string>
#include <map>

struct BigThing
{
    std::string v_;
    BigThing(const char* v) : v_{v} {
        std::cout << std::format("BigThing constructed {}\n", v_);
    }
};

using Mymap = std::map<std::string, BigThing>;
using RaceerMap = std::map<unsigned int, std::string>;

void printmap(Mymap& m)
{
    for(auto& [k, v] : m)
    {
        std::cout << std::format("[{}: {}] ", k, v.v_);
    }
    std::cout << std::endl;
}

void print_racer(const RaceerMap& m)
{
    std::cout << std::format("Rank:\n");
    for(const auto& [rank, racer] : m)
    {
        std::cout << std::format("{}:{}\n", rank, racer);
    }
}

template<typename M, typename K>
bool node_swap(M& m, K k1, K k2)
{
    auto node1{ m.extract(k1) };
    auto node2{ m.extract(k2) };

    if(node1.empty() || node2.empty())
    {
        return false;
    }
    std::swap(node1.key(), node2.key());
    m.insert(std::move(node1));
    // m.insert(std::move(node2));
    return true;
}
int main()
{
    Mymap m;
    m.emplace("Miles", "Trumpet");
    m.emplace("Hendrix", "Guitar");
    m.emplace("Krupa", "Drums");
    m.emplace("Zappa", "Guitar");
    m.emplace("Liszt", "Piano");

    printmap(m);

    std::cout << "emplace(Hendrix)\n";
    m.emplace("Hendrix", "Singer");

    std::cout << "try_emplace(Zappa)\n";
    m.try_emplace("Zappa", "Composer");

    printmap(m);

    RaceerMap racers {
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}
    };

    print_racer(racers);
    node_swap(racers, 3, 5);
    print_racer(racers);
}