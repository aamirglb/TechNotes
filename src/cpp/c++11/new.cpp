#include <iostream>
#include <new>

// check what is _alloca

int main() {
    int block {};
#ifdef THROW_VERSION
    try {
        while(true) {
            block++;
            // throw version of new
            new int[100000000ul];
        }
    } catch(const std::bad_alloc& e) {
        std::cout << "Allocated " << block << " blocks\n";
        std::cerr << e.what() << '\n';
    }
#else
    while(true) {
        // no throw version of new
        int *p = new(std::nothrow) int[100000000ul];
        ++block;
        if(p == nullptr) {
            std::cout << "Allocated " << block << " blocks\n";
            std::cerr << "Allocation return nullptr\n";
            break;
        }
    }
#endif
}