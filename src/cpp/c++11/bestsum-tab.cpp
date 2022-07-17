#include <iostream>
#include <vector>
#include <algorithm>

using IntList = std::vector<int32_t>;
using Table = std::vector<std::vector<int32_t>>;

IntList bestSum(int32_t targetSum, IntList numbers)
{
    // Table table(targetSum+1, {-1});
    // table[0].clear();

    Table table(targetSum+1);
    table[0] = {0};

    for(int32_t i = 0; i <= targetSum; ++i) {
        // if(table[i] != std::vector({-1})) {
        if(!table[i].empty()) {
            for(const auto& num : numbers) {
                if(i + num <= targetSum) {
                    auto combination = table[i];
                    combination.push_back(num);

                    if(table[i + num].empty() ||
                        table[i + num].size() > combination.size()) {
                            table[i + num] = combination;
                        }
                }
            }
        }
    }
    // remove zeros
    for(auto &v : table) {
        v.erase(std::remove(v.begin(), v.end(), 0), v.end());
    }

    return table[targetSum];
}

template <typename C>
void print(const C &c) {
    std::cout << "{ ";
    for (size_t i = 0; i < c.size(); ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << "}, " << std::endl;
}

int main()
{
    IntList v {5, 3, 4, 7};
    IntList v1 {2, 3, 5};
    IntList v2 {1, 4, 5};
    IntList v3 {1, 2, 5, 25};
    IntList v4 {10, 100};

    print(bestSum(7, v));
    print(bestSum(8, v1));
    print(bestSum(8, v2));
    print(bestSum(100, v3));
    print(bestSum(300, v4));
}