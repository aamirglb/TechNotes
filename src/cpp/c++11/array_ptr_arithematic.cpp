#include <iostream>

int main()
{
    int32_t A[4][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
        {10, 11, 12},
    };

    std::cout << "Size of int32_t  : " << sizeof(int32_t) << std::endl;
    std::cout << "Base Address of A: " << A << std::endl;
    std::cout << std::endl;

    for(size_t i = 0; i < 4; ++i) {
        for(size_t k = 0; k < 2; ++k) {
            for(size_t j = 0; j < 3; ++j) {
                if(k == 0)
                    std::cout << A[i][j] << "\t\t";
                else
                    std::cout << &A[i][j] << "\t";
            }
        std::cout << std::endl;
        }
    }

    std::cout << "A + 3        : " << A+3 << std::endl;
    std::cout << "*(A + 3)     : " << *(A+3) << std::endl;
    std::cout << "*(A + 2) + 3 : " << *(A+2)+3 << std::endl;
}