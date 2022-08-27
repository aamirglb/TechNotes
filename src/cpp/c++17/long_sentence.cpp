#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>

std::string filter_ws(const std::string& s) {
    const char *ws {" \r\n\t"};
    const auto a {s.find_first_not_of(ws)};
    const auto b {s.find_last_not_of(ws)};

    if(a != std::string::npos) {
        return s.substr(a, b);
    }
    return {};
}

std::multimap<size_t, std::string> get_sentence_stats(const std::string& content) {
    std::multimap<size_t, std::string> mm;

    const auto end_itr {content.end()};
    auto itr1 {content.begin()};
    auto itr2 {std::find(itr1, end_itr, '.')};

    while(itr1 != end_itr && std::distance(itr1, itr2) > 0) {
        std::string s {filter_ws({itr1, itr2})};

        if(s.length() > 0) {
            const auto words { std::count(s.begin(), s.end(), ' ') + 1};
            mm.emplace(std::make_pair(words, move(s)));
        }

        itr1 = std::next(itr2, 1);
        itr2 = std::find(itr1, end_itr, '.');
    }
    return mm;
}

int main() {
    std::cin.unsetf(std::ios::skipws);
    std::string content {std::istream_iterator<char>{std::cin}, {}};

    for(const auto& [word_count, sentence] : get_sentence_stats(content)) {
        std::cout << word_count << " words: " << sentence << ".\n";
    }
}