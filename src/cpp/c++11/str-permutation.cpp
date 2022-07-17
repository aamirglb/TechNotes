#include <iostream>
#include <string>
#include <vector>

void permutationV2(std::string s, int32_t low, int32_t high)
{
    if(low == high) {
        std::cout << s << std::endl;
    } else {
        for(int32_t i = low; i <= high; ++i) {
            std::swap(s[low], s[i]);
            permutationV2(s, low+1, high);
            std::swap(s[low], s[i]);
        }
    }
}

void permutation(std::string s, int32_t k)
{
    static std::vector<int32_t> mask(s.size(), 0);
    static std::string result(s.size(), '\0');
    static uint32_t count{};

//     for(const auto& c : mask) std::cout << c << ' ';
//     std::cout << std::endl;

//     // for(const auto& c : result) std::cout << c << ' ';
//     // std::cout << std::endl;
// return;
    if(s.size() == k) {
        std::cout << ++count << ". " << result << std::endl;
    } else {
        for(size_t i = 0; i < s.size(); ++i) {
            if(mask[i] == 0) {
                result[k] = s[i];
                mask[i] = 1;
                permutation(s, k+1);
                mask[i] = 0;
            }
        }
    }
}

int main()
{
    std::string s1 {"ABC"};
    // permutation(s1, 0);
    permutationV2(s1, 0, s1.size());
}