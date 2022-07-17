#include <iostream>
#include <algorithm>
#include <vector>

// print a 2D vector
template <typename C>
void print2d(const C &c) {
    for(size_t i = 0; i < c.size(); ++i) {
            std::cout <<  i << " => { ";
            for(size_t j = 0; j < c[i].size(); ++j) {
                std::cout << c[i][j] << ' ';
            }
            std::cout << "}, " << std::endl;
        }
        std::cout << std::endl;
}

template <typename C>
void print(const C &c) {
    std::cout << "{ ";
    for (size_t i = 0; i < c.size(); ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << "}, " << std::endl;
}

std::vector<int32_t> howSum(int32_t targetSum, std::vector<int32_t>& numbers)
{
    std::vector<std::vector<int32_t>> table(targetSum+1, {-1});

    table[0].clear();

    for(int32_t i = 0; i <= targetSum; ++i) {
        std::vector<int32_t> v{-1};
        if(table[i] != v) {
            for(const auto e : numbers) {
                if( (i + e) <= targetSum ) {
                    table[i + e] = table[i];
                    table[i + e].push_back(e);
                }
            }
        }
    }

    // print2d(table);

    // for(size_t i = 0; i < table.size(); ++i) {
    //     std::cout <<  i << " => { ";
    //     for(size_t j = 0; j < table[i].size(); ++j) {
    //         std::cout << table[i][j] << ' ';
    //     }
    //     std::cout << "}, " << std::endl;
    // }
    // std::cout << std::endl;
    return table[targetSum];
}

int main()
{
    std::vector<int32_t> v {5, 3, 4, 7};
    std::vector<int32_t> v1 {2, 3};
    std::vector<int32_t> v2 {2, 4};
    std::vector<int32_t> v3 {2, 3, 5};
    std::vector<int32_t> v4 {7, 14};

    print(howSum(7, v));
    print(howSum(7, v1));
    print(howSum(7, v2));
    print(howSum(8, v3));
    print(howSum(300, v4));
}