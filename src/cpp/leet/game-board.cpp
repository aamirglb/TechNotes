#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
using Board = std::vector<vector<int>>;

const unsigned int BOARD_SIDE = 3;
const unsigned char EMPTY = ' ';

void initBoard(Board& board) { // start questions + vector formation

    while (true) {
            cout << "Select start (R for random, I for input): ";
            string start;
            cin >> start;
            if (start == "i" or start == "I") {
                cout << "Input: ";
                string input = "";
                cin.ignore();
                getline(cin, input);
                cout << input << endl;
                istringstream is { input };
                // vector<vector<int>> board(3, vector<int>(3)); // board is now 2D vector including 9 user input values

                for (auto& row : board)
                {
                    for(auto& column : row)
                    {
                        is >> column; //cout << column << ', ';
                    }
                }
                print
                    // for(const auto& row : board)
                    // {
                    //     for (const auto column : row)
                    //     {
                    //         cout << column << " ";
                    //     }
                    //         cout << "\n";
                    // }
                break;
                }
      }
}

void printBoard(const Board& board)
{
    // prints a board vector whose elements are vectors
    cout << "=============" << endl;
    cout << "|   | 1 2 3 |" << endl;
    cout << "-------------" << endl;
    for(unsigned int row = 0; row < BOARD_SIDE; ++row)
    {
        cout << "| " << row + 1 << " | ";
        for(unsigned int column = 0; column < BOARD_SIDE; ++column)
        {
            if(board.at(row).at(column) == 0)
            {
                cout << EMPTY << " ";
            }
            else
            {
                cout << board.at(row).at(column) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

int main()
{
    Board board;
    //    { {1, 1, 4},
    //     {2, 1, 4},
    //     {2, 3, 5}
    //  };
    initBoard(board);
    printBoard(board);
}