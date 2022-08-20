#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> dx(8, 0);
      vector<int> dy(8, 0);

       dx={1,1, -1, -1, 2, 2, -2, -2};
       dy={2, -2, 2, -2, 1, -1, 1, -1};

       for(const auto& e: dx) cout << e << ' ';
       cout << endl;
}