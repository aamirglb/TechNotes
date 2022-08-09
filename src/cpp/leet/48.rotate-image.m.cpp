// cout << boolalpha << isSymmetric(root) << endl;

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void displayMatrix(vector<vector<int>> &matrix);

void rotate(vector<vector<int>>& matrix) {
    // rotate by 1
    auto left = 0;
    auto right = matrix.size() - 1;

    displayMatrix(matrix);
    while(left < right) {

        for(size_t i = 0; i < (right - left); ++i) {
            auto top = left;
            auto bottom = right;

            // save top left
            auto topLeft = matrix[top][left + i];

            // move bottom, left to top, left
            matrix[top][left + i] = matrix[bottom - i][left];

            // move bottom, right to bottom left
            matrix[bottom - i][left] = matrix[bottom][right - i];

            // move top, right to bottom, right
            matrix[bottom][right - i] = matrix[top + i][right];

            matrix[top + i][right] = topLeft;
        }
        left += 1;
        right -= 1;
    }
    displayMatrix(matrix);
}

void displayMatrix(vector<vector<int>> &matrix) {
    size_t m = matrix.size();
    size_t n = matrix[0].size();

    for(size_t i = 0; i < m; ++i) {
        for(size_t j = 0; j < n; ++j) {
            cout << setw(4) << matrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    vector<vector<int>> m1 {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    vector<vector<int>> m2 {
        {5, 1, 9, 11},
        {2, 4, 8, 10},
        {13, 3, 6, 7},
        {15, 14, 12, 16},
    };

    rotate(m1);
    rotate(m2);
}