#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

std::string filter_punctuation(const std::string& s) {
    const char *forbidden {".,:;' "};
    const auto start_idx {s.find_first_not_of(forbidden)};
    const auto end_idx {s.find_last_not_of(forbidden)};
    return s.substr(start_idx, end_idx - start_idx + 1);
}

int main() {
    std::map<std::string, size_t> words;
    size_t max_word_len {0};
    std::string max_string {};

    std::string word;
    while(std::cin >> word) {
        auto filtered {filter_punctuation(word)};
        max_word_len = std::max(max_word_len, filtered.length());
        if(filtered.length() > max_string.length())
            max_string = filtered;

        ++words[filtered];
    }

    std::vector<std::pair<std::string, size_t>> word_counts;
    word_counts.reserve(words.size());
    std::move(words.begin(), words.end(), std::back_inserter(word_counts));

    std::sort(word_counts.begin(), word_counts.end(),
        [](const auto&a, const auto& b) {
            return a.second > b.second;
        });

    std::cout << "#  " << std::setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
    for(const auto& [word, count] : word_counts) {
        std::cout << std::setw(max_word_len + 3) << word << " #" << count << '\n';
    }
    std::cout << "max string: " << max_string << ": " << max_word_len << '\n';
    std::cout << "done...\n";
}