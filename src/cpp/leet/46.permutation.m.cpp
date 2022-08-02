// Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> result;
void backtrack(vector<int>& v, int k, vector<int> &mask, vector<int> &res) {

    if(k == v.size()) {
        result.push_back(res);
        for(auto& e:res) cout << e << ' ';
        cout << endl;
    } else {
        for(size_t i = 0; i < v.size(); ++i) {
            if(mask[i] == 0) {
                res[k] = v[i];
                mask[i] = 1;
                backtrack(v, k+1, mask, res);
                mask[i] = 0;
            }
        }
    }
}
vector<vector<int>> permute(vector<int>& nums) {
    vector<int> mask(nums.size(), 0);
    vector<int> res(nums.size(), 0);
    backtrack(nums, 0, mask, res);
    return result;
}

int main() {
    vector<int> v {1, 2, 3};
    permute(v);
    result.clear();

    cout << "\nTC-2\n";
    vector<int> v2 {0, -1, 1};
    permute(v2);
    result.clear();

    cout << "\nTC-3\n";
    vector<int> v3 {3, 2, 1};
    permute(v3);
    result.clear();
}