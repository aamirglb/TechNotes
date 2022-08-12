// Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
// 1. Each row must contain the digits 1-9 without repetition.
// 2. Each column must contain the digits 1-9 without repetition.
// 3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool validateRow(const vector<char> &row) {
    unordered_map<char, int> m;
    for(const auto& ch: row) {
        if(ch != '.') {
            if(m.count(ch) > 0) {
                cout << "found duplicate " << ch << endl;
                return false;
            }
            m[ch]++;
        }
    }
    return true;
}

bool validateSubgrid(int id, vector<vector<char>>& board) {
    int r = (id / 3) * 3;
    int c = (id % 3) * 3;
    vector<char> v;
    for(int i = r; i < r+3; ++i) {
        for(int j = c; j < c+3; ++j) {
            v.push_back(board[i][j]);
        }
    }
    return validateRow(v);

    // cout << "grid: " << id << endl;
    // for(size_t i = 0; i < 9; ++i) {
    //     cout << v[i] << ' ';
    //     if((i+1) % 3 == 0) cout << endl;
    // }
    // cout << endl;
}

bool isValidSudoku(vector<vector<char>>& board) {

    // validate rows
    for(const auto& row: board) {
        if(!validateRow(row))
            return false;
    }

    // validate columns
    for(size_t col = 0; col < board.size(); ++col) {
        vector<char> v;
        for(size_t row = 0; row < board[col].size(); ++row) {
            v.push_back(board[row][col]);
        }
        if(!validateRow(v))
            return false;
    }

    // validate sub-grid
    for(size_t id = 0; id < 9; ++id) {
        if(!validateSubgrid(id, board))
            return false;
    }
    return true;
}

/*

*/
int main() {
    vector<vector<char>> board  {{'5','3','.','.','7','.','.','.','.'}
                                ,{'6','.','.','1','9','5','.','.','.'}
                                ,{'.','9','8','.','.','.','.','6','.'}
                                ,{'8','.','.','.','6','.','.','.','3'}
                                ,{'4','.','.','8','.','3','.','.','1'}
                                ,{'7','.','.','.','2','.','.','.','6'}
                                ,{'.','6','.','.','.','.','2','8','.'}
                                ,{'.','.','.','4','1','9','.','.','5'}
                                ,{'.','.','.','.','8','.','.','7','9'}};

    cout << boolalpha << isValidSudoku(board) << endl;

}