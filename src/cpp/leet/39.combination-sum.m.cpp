// Given an array of distinct integers candidates and a target integer target, return a list of all
// unique combinations of candidates where the chosen numbers sum to target.

#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

vector<int> helper()
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());

    if(candidates[candidates.size() - 1] < target) return {};
}

int main() {

}