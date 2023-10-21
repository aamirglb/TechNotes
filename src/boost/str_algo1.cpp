#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <string>
#include <locale>
#include <iostream>
#include <vector>

#include <fmt/core.h>

int main()
{
    std::string s = "boost c++ libraries";
    fmt::print("{}\n", boost::algorithm::to_upper_copy(s));

    std::string s2{"Boost C++ k\xfct\xfcphaneleri"};
    std::string upper_case1 = boost::algorithm::to_upper_copy(s2);
    // std::string upper_case2 = boost::algorithm::to_upper_copy(s2, std::locale("us"));

    fmt::print("{}\n", upper_case1);
    // fmt::print("{}\n", upper_case2);

    // Remove characters from string
    fmt::print("erase_first_copy: {}\n", boost::algorithm::erase_first_copy(s, "s"));
    fmt::print("erase_nth_copy(): {}\n", boost::algorithm::erase_nth_copy(s, "s", 0));
    fmt::print("erase_last_copy: {}\n", boost::algorithm::erase_last_copy(s, "s"));
    fmt::print("erase_all_copy: {}\n", boost::algorithm::erase_all_copy(s, "s"));
    fmt::print("erase_head_copy: {}\n", boost::algorithm::erase_head_copy(s, 5));
    fmt::print("erase_tail_copy: {}\n", boost::algorithm::erase_tail_copy(s, 9));

    boost::iterator_range<std::string::iterator> r = boost::algorithm::find_first(s, "c++");
    fmt::print("{}\n", r);
    std::cout << r << std::endl;

    std::vector<std::string> vs{"boost", "c++", "libraries"};
    fmt::print("{}\n", boost::algorithm::join(vs, "-"));

    // replace character
    fmt::print("{}\n", boost::algorithm::replace_first_copy(s, "+", "*"));
    fmt::print("{}\n", boost::algorithm::replace_nth_copy(s, "+", 0, "*"));
    fmt::print("{}\n", boost::algorithm::replace_last_copy(s, "+", "*"));
    fmt::print("{}\n", boost::algorithm::replace_all_copy(s, "+", "*"));
    fmt::print("{}\n", boost::algorithm::replace_head_copy(s, 5, "BOOST"));
    fmt::print("{}\n", boost::algorithm::replace_tail_copy(s, 9, "LIBRARIES"));

    // trim characters
    std::string s3{"\t Boost C++ Libraries \t"};
    fmt::print("s3 = {}\n", s3);
    fmt::print("_{}_\n", boost::algorithm::trim_left_copy(s3));
    fmt::print("_{}_\n", boost::algorithm::trim_right_copy(s3));
    fmt::print("_{}_\n\n", boost::algorithm::trim_copy(s3));

    // trim characters with predicates
    std::string s4{"--Boost C++ Libraries--"};
    fmt::print("{}\n", boost::algorithm::trim_left_copy_if(s4, boost::algorithm::is_any_of("-")));
    fmt::print("{}\n", boost::algorithm::trim_right_copy_if(s4, boost::algorithm::is_any_of("-")));
    fmt::print("{}\n", boost::algorithm::trim_copy_if(s4, boost::algorithm::is_any_of("-")));

    std::string s5{"123456789Boost C++ Libraries123456789"};
    fmt::print("\n{}\n", boost::algorithm::trim_copy_if(s5, boost::algorithm::is_digit()));

    fmt::print("{}\n", boost::algorithm::starts_with(s4, "--Boost"));
    fmt::print("{}\n", boost::algorithm::ends_with(s4, "Libraries--"));
    fmt::print("{}\n", boost::algorithm::contains(s, "C++"));

    {
        // regex
        std::string s5{"Boost C++ Libraries"};
        boost::iterator_range<std::string::iterator> r = boost::algorithm::find_regex(s5, boost::regex{"\\W\\+\\+"});
        std::cout << r << std::endl;
    }
}
