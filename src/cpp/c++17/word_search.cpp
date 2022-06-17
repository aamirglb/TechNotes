#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <optional>
#include <iterator>
#include <set>
#include <chrono>

using word_list_t = std::vector<std::string>;
using word_t = std::string;

// std::optional<std::pair<std::string, int32_t>> find_word(word_list_t &list, word_t word)
// {
//     if(auto pos = std::find(list.begin(), list.end(), word); pos != list.end()) {
//         return make_pair(*pos, std::distance(list.begin(), pos) + 1);
//     } else {
//         return std::nullopt;
//     }
// }

void find_all_alternate(word_list_t &list, word_t word)
{
    auto start = std::chrono::steady_clock::now();
    word_list_t search_list;

    // Filter out bigger words
    std::copy_if(list.begin(), list.end(),
                std::back_inserter(search_list),
                [=](auto s){
                    return s.size() == word.size();
        });
    // std::cout << "search list size: " << search_list.size() << std::endl;

    auto len = word.size();
    std::set<std::string> results;

    while(len--) {
        std::string alt = word.substr(1, word.size()-1);
        for(const auto& w : search_list) {
            auto found = w.find(alt);
            if(found != std::string::npos) {
                results.insert(w);
            }
        }
        std::rotate(word.begin(), word.begin()+1, word.end());
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << "All possible alternatives word of '" << word << "' are: " << std::endl;
    for(const auto &s : results) std::cout << s << std::endl;
    std::cout << std::endl;
    std::cout << "Total: " << results.size() << std::endl;


    std::cout << "Elapsed Time: " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - start).count() << "[ns]" << std::endl;
    std::cout << "Elapsed Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "[ms]" << std::endl;

}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        std::cerr << "ERROR: Run the program as follows\n";
        std::cerr << "./word_search <word>\n";
        return -1;
    }

    std::string word_to_search = argv[1];
    std::ifstream in_file("words.txt", std::ios::in);
    if(!in_file.is_open()) {
        std::cerr << "Unable to open words.txt file\n";
        return -1;
    }

    std::string word;
    word_list_t word_list;

    while(in_file >> word) {
        word_list.push_back(word);
    }
    in_file.close();

    find_all_alternate(word_list, word_to_search);
}