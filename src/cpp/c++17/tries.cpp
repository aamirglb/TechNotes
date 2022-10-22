// tries - prefix tree
#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <sstream>

template <typename T>
class trie {
    std::map<T, trie> tries;
public:
    template <typename Itr>
    void insert(Itr itr, Itr end_itr) {
        if(itr == end_itr) return;
        tries[*itr].insert(std::next(itr), end_itr);
    }

    template <typename C>
    void insert(const C &c) {
        insert(c.begin(), c.end());
    }

    // template <typename T>
    void insert(const std::initializer_list<T> &il) {
        insert(il.begin(), il.end());
    }

    // template <typename T>
    void print(std::vector<T> &v) const {
        if(tries.empty()) {
            std::copy(v.begin(), v.end(),
            std::ostream_iterator<T>{std::cout, ", "});
            std::cout << '\n';
        }

        for(const auto &p : tries) {
            v.push_back(p.first);
            p.second.print(v);
            v.pop_back();
        }
    }

    // template <typename T>
    void print() const {
        std::vector<T> v;
        print(v);
    }

    template <typename Itr>
    std::optional<std::reference_wrapper<const trie>>
    subtrie(Itr itr, Itr end_itr) const {
        if(itr == end_itr) {
            return ref(*this);
        }
        auto found {tries.find(*itr)};
        if(found == tries.end()) return {};
        return found->second.subtrie(std::next(itr), end_itr);
    }

    template <typename C>
    auto subtrie(const C &c) {
        return subtrie(c.begin(), c.end());
    }
};

int main() {
    trie<std::string> t;
    std::vector<std::string> input {
        "hi how are you",
        "hi i am great thanks",
        "what are you doing",
        "i am watching a movie",
    };
    for(auto &s : input) {
        std::stringstream ss{s};
        std::vector<std::string> in;
        std::string token;
        while(ss >> token) {
            in.push_back(token);
        }
        t.insert(in);
        // for(const auto &e: in) std::cout << e << ", ";
        // std::cout << '\n';
    }

    std::cout << "Recorded sentences:\n";
    t.print();
    std::cout << "\nPossible suggestions after \"hi\":\n";
    if(auto st{t.subtrie(std::initializer_list<std::string>{"hi"})}; st) {
        st->get().print();
    }
    // t.insert({""})
}