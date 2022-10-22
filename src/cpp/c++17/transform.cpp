#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};

    std::transform(v.begin(), v.end(),
        std::ostream_iterator<int>(std::cout, ", "),
        [](int i){ return i * i; });
    std::cout << '\n';

    auto int_to_string = [](int i) {
        std::stringstream ss;
        ss << i << "^2 = " << i * i;
        return ss.str();
    };

    std::vector<std::string> vs;
    std::transform(v.begin(), v.end(), std::back_inserter(vs),
        int_to_string);
    std::copy(vs.begin(),
              vs.end(),
              std::ostream_iterator<std::string>{std::cout, "\n"});
}