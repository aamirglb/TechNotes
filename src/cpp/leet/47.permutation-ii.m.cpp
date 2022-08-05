// Given a collection of numbers, nums, that might contain duplicates,
// return all possible unique permutations in any order.

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void backtracking(vector<int>& n,
    unordered_map<int, int> &m,
    vector<int> &p,
    vector<vector<int>> &r)
{
    if(p.size() == n.size()) {
        r.push_back(p);
    }

    for(const auto& [k, v] : m) {
        if(m[k] > 0) {
            p.push_back(k);
            --m[k];

            backtracking(n, m, p, r);
            ++m[k];
            p.pop_back();
        }
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
    unordered_map<int, int> count;
    vector<vector<int>> res;
    vector<int> perm;

    for(auto & n : nums)
        count[n]++;

    backtracking(nums, count, perm, res);
    return res;
}

int main() {
    vector<int> v{1, 1, 2};
    auto r = permuteUnique(v);
    for(auto &p : r) {
        for(auto &e : p) {
            cout << e << ' ';
        }
        cout << endl;
    }

    cout << "\nTC-2\n";
    vector<int> v2{1, 2, 3};
    r = permuteUnique(v2);
    for(auto &p : r) {
        for(auto &e : p) {
            cout << e << ' ';
        }
        cout << endl;
    }
}