#include "grid.hpp"

int main()
{
    Grid<int> iGrid;
    Grid<double> dGrid { 4, 4 };

    for(size_t i{}; i < Grid<int>::DefaultWidth; ++i) {
        iGrid.at(i, i) = i;
    }

    for(size_t i{}; i < Grid<int>::DefaultWidth; ++i) {
        auto j = i + 1;
        iGrid.at(i, (Grid<int>::DefaultWidth - i - 1)) = j * j;
    }

    // for(size_t i{Grid<int>::DefaultWidth}; i > 0; --i) {
    //     auto j = i - 1;
    //     iGrid.at(j, j) = (j * j);
    //     // fmt::print("{}, {}\n", i, i*i);
    // }
    // int x = iGrid.at(0, 0).value_or(0);

    iGrid.display();
    dGrid.display();
    // fmt::print("{}\n", x);

    // Use template specialization
    Grid<const char*> strGrid{4, 4};
    const char* dummy { "dummy" };
    strGrid.at(0, 0) = "hello";
    strGrid.at(0, 1) = dummy;
    strGrid.at(1, 0) = dummy;
    strGrid.at(1, 1) = "there";

    strGrid.display();
}