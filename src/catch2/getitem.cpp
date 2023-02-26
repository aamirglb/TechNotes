#include <vector>
#include <catch2/catch_test_macros.hpp>

// g++ -Wall -Werror -pedantic -IC:\Users\aamir.ali\Documents\playground\Programs\libraries\catch2\include getitem.cpp -L C:\Users\aamir.ali\Documents\playground\Programs\libraries\catch2\lib -lCatch2Main -lCatch2

long INVALID_INDEX {-1};

long GetNextItem(long index, const std::vector<int>& v)
{
    bool isImageListEmpty = v.size() == 0;
    long lastElemIndex = v.size() - 1;

    // Request for 1st element index, but list is empty
    if (index == INVALID_INDEX && isImageListEmpty)
    {
        return INVALID_INDEX;
    }
    return (index != lastElemIndex) ? (index + 1) : INVALID_INDEX;   
}

std::vector<int> v1{1, 2, 3, 4};
TEST_CASE( "Get correct index to next item", "[getnexitem]") {
    REQUIRE( GetNextItem(INVALID_INDEX, {}) == INVALID_INDEX);
    REQUIRE( GetNextItem(INVALID_INDEX, v1) == 0);
    REQUIRE( GetNextItem(0, v1) == 1);
    REQUIRE( GetNextItem(1, v1) == 2);
    REQUIRE( GetNextItem(2, v1) == 3);        
    REQUIRE( GetNextItem(3, v1) == INVALID_INDEX);
    REQUIRE( GetNextItem(3, v1) == 4);
    // REQUIRE( GetNextItem(INVALID_INDEX, v1) == 0);
}