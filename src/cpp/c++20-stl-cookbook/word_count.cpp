#include <iostream>
#include <format>
#include <regex>
#include <ranges>
#include <map>
#include <vector>
#include <string>

constexpr const char* re{"((\\w+))"};

int main()
{
    std::map<std::string, int> word_map{};
    std::vector<std::pair<std::string, int>> wordvec{};
    std::regex word_re(re);
    size_t total_words{};

    for(std::string s{}; std::cin >> s;)
    {
        auto words_begin{
            std::sregex_iterator(s.begin(), s.end(), word_re)
        };
        auto words_end{ std::sregex_iterator()};
        for(auto it{words_begin}; it != words_end; ++it)
        {
            std::smatch match{ *it };
            auto word_str{match.str()};
            std::ranges::transform(word_str, word_str.begin(), 
                [](unsigned char c){ return tolower(c); });

            auto [map_it, result] = word_map.try_emplace(word_str, 0);
            auto& [w, count] = *map_it;
            ++total_words;
            ++count;
        }
    }
}