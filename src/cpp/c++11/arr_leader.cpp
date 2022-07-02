#include <iostream>
#include <vector>

int main()
{
    int a[] = {63, 70, 80, 33, 33, 47, 20};
    int n = 7;

    std::vector<int> result;

    for(int i = 0; i < n; ++i) {
        int sum = 0;
        for(int j = i+1; j < n; ++j) {
            sum += a[j];
        }
        std::cout << i << " " << a[i] << " " << sum << std::endl;
        if(a[i] >= sum) result.push_back(a[i]);
    }
    for(const auto& e : result) std::cout << e << ' ';

    // result.push_back(a[n-1]);
    // return result;
}