#include <iostream>
#include <queue>
#include <tuple>
#include <string>

int main() {
    using item_type = std::pair<int, std::string>;
    std::priority_queue<item_type> q;
    std::initializer_list<item_type> lst {
        {1, "dishes"},
        {0, "watch tv"},
        {2, "do homework"},
        {0, "read comics"},
        {3, "read books"},
        {2, "excersice"},
    };

    for(const auto& p :lst) q.push(p);

    while(!q.empty()) {
        std::cout << q.top().first << ": " << q.top().second << '\n';
        q.pop();
    }
    std::cout << std::endl;
}