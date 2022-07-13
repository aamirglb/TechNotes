#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<std::string> num_names { "one", "two", "six", "ten", "four",
                    "five", "nine", "three", "seven", "eight"};
    auto partition_checker = [](auto s) { return s.size() == 3; };

    if(std::is_partitioned(num_names.begin(), num_names.end(), partition_checker)) {
        std::cout << "num_names is partitioned." << std::endl;

        // Get the distance of partition point
        auto pos = std::partition_point(num_names.begin(), num_names.end(), partition_checker);
        std::cout << "First string with size > 3: " << *pos
                  << " at " << std::distance(num_names.begin(), pos) + 1 << " from begining" << std::endl;
    } else {
        std::cout << "num_names is not partitioned" << std::endl;
    }


// int main()
// {
//     std::vector<int32_t> v {5, 3, 9, 1, 3, 4, 8, 2, 6};
//     auto isOdd = [](int32_t e) { return e%2 == 1; };
//     auto isEven = [](int32_t e) { return e%2 == 0; };

//     std::vector<std::string> number_names { "one", "two", "six", "ten", "four", "five", "nine", "three"};
//     auto partition_checker = [](auto s) { return s.size() == 3; };

//     if(std::is_partitioned(number_names.cbegin(), number_names.cend(), partition_checker)) {
//         std::cout << "collection is partitioned.\n";
//         auto pos = std::partition_point(number_names.cbegin(), number_names.cend(), partition_checker);
//         std::cout << "First string with size > 3: " << *pos
//                   << " at " << std::distance(number_names.begin(), pos) + 1 << std::endl;
//     } else {
//         std::cout << "collection is not partitioned" << std::endl;
//     }

    // if(std::is_partitioned(v.cbegin(), v.cend(), isOdd)) {
    //     std::cout << "collection is partitioned.\n";
    //     auto pos = std::partition_point(v.cbegin(), v.cend(), isOdd);
    //     std::cout << "First even element: " << *pos << " at " << std::distance(v.begin(), static_cast<ForwardIter>pos) + 1 << std::endl;
    // } else {
    //     std::cout << "collection is not partitioned\n";
    // }

    // if(std::is_partitioned(v.cbegin(), v.cend(), isEven)) {
    //     std::cout << "collection is partitioned.\n";
    //     auto pos = std::partition_point(v.cbegin(), v.cend(), isEven);
    //     std::cout << "First even element: " << *pos << " at " << std::endl;
    // } else {
    //     std::cout << "collection is not partitioned\n";
    // }
}


