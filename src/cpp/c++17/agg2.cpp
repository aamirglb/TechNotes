#include <iostream>
#include <array>

struct MyArray : std::array<int, 2ul>
{
     using std::array<int, 2ul>::array;
};

int main() {
    MyArray a{ {1, 2} };
}


