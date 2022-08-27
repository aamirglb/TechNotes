#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

int main() {
    std::istream_iterator<int> cin_itr {std::cin};
    std::istream_iterator<int> cin_end;

    std::deque<int> dq;
    std::copy(cin_itr, cin_end, std::back_inserter(dq));

    // insert into the middle of dq
    std::istringstream sstr{"123 456 789"};

    auto q_middle {std::next(dq.begin(), static_cast<int>(dq.size())/2)};
    std::copy(std::istream_iterator<int>{sstr}, {}, std::inserter(dq, q_middle));

    std::initializer_list<int> il2 {-1, -2, -3};
    std::copy(il2.begin(), il2.end(), std::front_inserter(dq));

    std::copy(dq.begin(), dq.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;
}