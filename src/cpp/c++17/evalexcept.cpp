#include <iostream>
#include <vector>

void print10elem(const std::vector<int32_t>& v) {
    for(int i = 0; i < 10; ++i) {
        std::cout << "value: " << v.at(i) << '\n';
    }
}

int main()
{
    try {
        std::vector<int32_t> vec{7, 14, 21, 28};
        print10elem(vec);
    }
    catch(const std::exception& e) {
        std::cerr << "EXCEPTION: " << e.what() << '\n';
    }
    catch(...) {
        std::cerr << "EXCPETION of unknow type\n";
    }
}