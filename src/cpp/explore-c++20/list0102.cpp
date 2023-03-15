#include <cerrno>
#include <cstdlib>
// import std;
#include <algorithm>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <system_error>
#include <vector>

template <class C>
struct text : std::basic_string<C>
{
    using super = std::basic_string<C>;
    constexpr text() noexcept : super{} {}
    text(text &&) = default;
    text(const text &) = default;
    text &operator=(const text &) = default;
    text &operator=(text &&) = default;
    constexpr explicit operator bool() const noexcept
    {
        return not this->empty();
    }
};

template <class Ch>
auto read(std::basic_istream<Ch> &in) -> std::vector<text<Ch>>
{
    std::vector<text<Ch>> result;

    text<Ch> line;
    while (std::getline(in, line))
    {
        result.emplace_back(std::move(line));
    }
    return result;
}

int main(int argc, char *argv[])
{
    try
    {
        std::cin.exceptions(std::ios_base::badbit);
        std::vector<text<char>> text;
        if (argc < 2)
        {
            text = read(std::cin);
        }
        else
        {
            std::ifstream in{argv[1]};
            if (not in)
            {
                std::cout << argv[1] << ": " << std::system_category().message(errno) << '\n';
                return EXIT_FAILURE;
            }
            text = read(in);
        }

        const std::locale &loc{std::locale(argc >= 3 ? argv[2] : "")};
        const std::collate<char> &collate{std::use_facet<std::collate<char>>(loc)};
        std::ranges::sort(text, [&collate](const auto &a, const auto &b)
                          { return collate.compare(to_address(cbegin(a)), to_address(cend(a)),
                                                   to_address(cbegin(b)), to_address(cend(b))) < 0; });
        for (const auto &line : text)
        {
            std::cout << line << '\n';
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << '\n';
        std::cerr << "Terminating program." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    catch (...)
    {
        std::cerr << "Caught unknow exception type." << std::endl;
        std::cerr << "Terminating program." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}
