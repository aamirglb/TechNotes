// Given an integer numRows, return the first numRows of Pascal's triangle.
// In Pascal's triangle, each number is the sum of the two numbers directly above it as shown:

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> res {{1}};
    if(numRows == 1) return res;

    for(int i = 0; i< numRows - 1; ++i) {
        int n = res.size() - 1;
        vector<int> tmp = res[n];
        tmp.insert(tmp.begin(), 0);
        tmp.push_back(0);
        vector<int> v;
        for(int j = 0; j < n+2; ++j) {
            v.push_back(tmp[j] + tmp[j+1]);
        }
        res.push_back(v);
    }

    for(const auto& row: res) {
        for(const auto& col : row) {
            cout << col << ' ';
        }
        cout << endl;
    }
    return res;
}

int main(int argc, char *argv[]) {
    int n = 3;
    if(argc > 1) {
        n = stoi(argv[1]);
    }

    generate(n);
}
