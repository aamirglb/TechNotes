// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water),
// return the number of islands.
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or
// vertically. You may assume all four edges of the grid are all surrounded by water.

#include <vector>
#include <array>
#include <queue>
#include <fmt/format.h>
#include <fmt/ranges.h>
using namespace std;

void bfs(vector<vector<char>>& grid,
         vector<vector<bool>>& visited,
         int i,
         int j) {

    std::queue<pair<int, int>> q;
    q.push(make_pair(i, j));

    visited[i][j] = true;

    while(!q.empty()) {
        auto &[row, col] = q.front();
        q.pop();

        array<pair<int, int>, 4> directions {
            make_pair(1,  0),
            make_pair(-1, 0),
            make_pair(0,  1),
            make_pair(0, -1),
        };

        for(const auto& [dr, dc] : directions) {
            auto r = row + dr;
            auto c = col + dc;

            auto isValidIndex = [=](int i, int j) -> bool {
                if(i >= 0 && i < grid.size() &&
                    j >= 0 && j < grid[0].size()) return true;
                return false;
            };

            if(isValidIndex(r, c) && grid[r][c] == '1' && !visited[r][c]) {
                q.push(make_pair(r, c));
                visited[r][c] = true;
            }
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    if(grid.size() == 0) return 0;
    int32_t islands {};
    auto rows = grid.size();
    auto cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < cols; ++j) {
            if(grid[i][j] == '1' && !visited[i][j]) {
                bfs(grid, visited, i, j);
                islands += 1;
            }
        }
    }
    return islands;
}

int main() {
    vector<vector<char>> grid1 = {
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'},
    };

    vector<vector<char>> grid2 = {
        {'1', '1', '1', '1', '1', '0', '1', '1', '1', '1'},
        {'1', '0', '1', '0', '1', '1', '1', '1', '1', '1'},
        {'0', '1', '1', '1', '0', '1', '1', '1', '1', '1'},
        {'1', '1', '0', '1', '1', '0', '0', '0', '0', '1'},
        {'1', '0', '1', '0', '1', '0', '0', '1', '0', '1'},
        {'1', '0', '0', '1', '1', '1', '0', '1', '0', '0'},
        {'0', '0', '1', '0', '0', '1', '1', '1', '1', '0'},
        {'1', '0', '1', '1', '1', '0', '0', '1', '1', '1'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '0', '1'},
        {'1', '0', '1', '1', '1', '1', '1', '1', '1', '0'}
    };

    fmt::print("{}\n", numIslands(grid2));
}


