// #include <iostream>
// #include <regex>

// int main() {
//     std::cout << "Hello, World!" << std::endl;
//     std::regex reg("");
//     return 0;
// }

// class Foo {
//     public:
//     int baz() const { return 1;}
//     protected:
//     int i;
// };

// class Bar : public Foo {
//     int i; // Triggers warning
//     public:
//     int baz() const { return 2;}
// };

// int main() {
//     Bar b;
//     Foo& f = b;
//     return f.baz(); // returns 1
// }

#include <functional>
#include <iostream>
#include <map>

// void MIN(std::string input) { std::cout << "MIN\n"; }
// void MAX(std::string input) { std::cout << "MAX\n"; }
// void AVG(std::string input) { std::cout << "AVG\n"; }

// std::map<std::string, std::function<void(std::string)>> callTable {
//     {"max",  MIN},
//     {"min", MIN},
//     {"avg", AVG},
// };

#include <iostream>
#include <vector>
#include <fstream>

struct Edge {
    int source, dest, weight;
};

std::ostream& operator<<(std::ostream& os, const Edge edge) {
    os << "(" << edge.source << ", " << edge.dest << ", " << edge.weight << ")\n";
    return os;
}

int main()
{
    // initialize edges as per the above diagram
    // (u, v, w) represent edge from vertex `u` to vertex `v` having weight `w`
    std::vector<Edge> edges;

    std::ifstream fin("in.txt");

    if (!fin.is_open()) {
        std::cerr << "fail";
        return 1;
    }

    int s, d, w;
    while (fin >> s >> d >> w) {
        edges.emplace_back(Edge{s, d, w});
    }
    fin.close();

    for (auto &edge: edges) {
        std::cout << edge;
    }

    return 1;
}

