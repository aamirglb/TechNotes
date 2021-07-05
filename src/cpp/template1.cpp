#include <iostream>
#include <cstdint>

using namespace std;

struct Number {
    Number(): _n{0}
    {}
    Number(int32_t n): _n{n}
    {}

    void reset(int32_t n) {
        _n = n;
    }
    friend bool operator<(const Number n1, const Number n2) {
        cout << __FUNCTION__   << " called\n"; 
        if( n1._n < n2._n) 
            return true;
        else
            return false;
    }

    friend ostream& operator<<(ostream& out, const Number n) {
        out << n._n << '\n';
        return out;
    }
    int32_t _n;
};

template<typename T>
T max(T a, T b) {
    // if b < a then yield a else yield b
    return b < a ? a : b;
}

int main() {
    Number n1;
    Number n2{10};
    // static_assert(false, "Always fails");
    cout << n1 << n2;

    cout << "Max: " << ::max<Number>(n1, n2); 

    n1.reset(50);
    cout << "Max: " << ::max<Number>(n1, n2); 
}