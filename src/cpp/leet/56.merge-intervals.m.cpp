// Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals,
// and return an array of the non-overlapping intervals that cover all the intervals in the input.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isInInterval(int start, vector<int> &interval) {
    // cout << "isInInterval: [" << start << ", " << end << "]\n";
    if(start <= interval[1])
        return true;
    else
        return false;
}

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> result;
    if(intervals.size() == 0) return result;

    sort(intervals.begin(), intervals.end());
    vector<int> currInterval {intervals[0]};

    for(size_t i = 1; i < intervals.size(); ++i) {

        if(intervals[i][0] <= currInterval[1]) {
            currInterval[1] = max(currInterval[1], intervals[i][1]);
        } else {
            result.push_back(currInterval);
            currInterval = intervals[i];
        }
    }
    result.push_back(currInterval);

    for(auto &v : result) {
        cout << "[" << v[0] << ", " << v[1] << "]\n";
    }
    return result;
}

int main()
{
    vector<vector<int>> input {
        // {6, 9},
        {1, 3},
        {2, 4},
        {2, 6},
        {8, 10},
        {10, 18},
        {20, 25},
    };
    merge(input);

    vector<vector<int>> input2 {
        {1, 4},
        {4, 5}
    };

    cout << "\n\nTC-2\n";
    merge(input2);
    cout << "done..\n";
}