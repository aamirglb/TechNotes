#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class AddValue {
private:
    T theValue;
public:
    AddValue(const T& v) : theValue{v} {
        std::cout << __FUNCTION__ << " called\n";
    }

    void operator()(T& elem) const {
        elem += theValue;
    }
};

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    for_each(v.begin(), v.end(), AddValue<int>(10));

    for_each(v.begin(), v.end(), AddValue<int>(*v.begin()));
}

