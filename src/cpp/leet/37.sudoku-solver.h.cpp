#include <iostream>
#include <vector>
#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>
using namespace std;

/*
fmt::print(fmt::emphasis::bold | fg(fmt::color::red),
           "Elapsed time: {0:.2f} seconds", 1.23);
*/

vector<vector<char>> backup;
void printBoard(const vector<vector<char>>& board) {
    for(size_t i = 0; i < 9; ++i) {
        for(size_t j = 0; j < 9; ++j) {
            if(backup[i][j] == '.' && board[i][j] != '.') {
                fmt::print(fg(fmt::color::red), "{} ", board[i][j]);
            } else {
                fmt::print("{} ", board[i][j]);
            }
        }
        fmt::print("\n");
    }
    fmt::print("\n\n");
}

pair<int, int> findStartEnd(int coord) {
    pair<int, int> se;
    if(coord < 3) {
        se.second = 2;
    } else if(coord < 6) {
        se.first = 3;
        se.second = 5;
    } else if(coord < 9) {
        se.first = 6;
        se.second = 8;
    }
    return se;
}

bool isValid(vector<vector<char>>& board, int row, int col, char val) {
    for(int i = 0; i < 9; ++i) {
        if(board[row][i] == val) return false;
        if(board[i][col] == val) return false;
    }

    const auto &[s1, e1] = findStartEnd(row);
    const auto &[s2, e2] = findStartEnd(col);

    for(int i = s1; i <= e1; ++i) {
        for(int j = s2; j <= e2; ++j) {
            if(board[i][j] == val)
                return false;
        }
    }
    return true;
}

bool helper(vector<vector<char>>& board, int row, int col) {
    if(col == 9) {
        row += 1;
        col = 0;
    }
    if(row == 9) return true;

    // element already filled
    if(board[row][col] != '.') {
        return helper(board, row, col+1);
    }

    // DFS for all valid options
    for(char i = '1'; i <= '9'; ++i) {
        if(!isValid(board, row, col, i))
            continue;
        board[row][col] = i;
        if(helper(board, row, col + 1)) {
            return true;
        }
        board[row][col] = '.';
    }
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    vector<vector<char>> backup {board};
    helper(board, 0, 0);
}

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
    backup = board;
    printBoard(board);
    solveSudoku(board);
    printBoard(board);

}