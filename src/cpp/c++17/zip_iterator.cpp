#include <iostream>
#include <vector>
#include <numeric>
#include <valarray>

class zip_iterator {
    using itr_type = std::vector<double>::iterator;

    itr_type itr1;
    itr_type itr2;
public:
    zip_iterator(itr_type it1, itr_type it2)
    : itr1{it1}
    , itr2{it2}
    {}

    zip_iterator& operator++() {
        ++itr1;
        ++itr2;
        return *this;
    }

    bool operator!=(const zip_iterator& other) const {
        return itr1 != other.itr1 && itr2 != other.itr2;
    }

    bool operator==(const zip_iterator& other) const {
        return !operator!=(other);
    }

    std::pair<double, double> operator*() const {
        return {*itr1, *itr2};
    }
};

namespace std {
    template <>
    struct iterator_traits<zip_iterator> {
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<double, double>;
        using difference_type = long int;
    };
}

class zipper {
    using vec_type = std::vector<double>;
    vec_type &vec1;
    vec_type &vec2;

public:
    zipper(vec_type &va, vec_type &vb)
    : vec1{va}
    , vec2{vb}
    {}

    zip_iterator begin() const {
        return {std::begin(vec1), std::begin(vec2)};
    }

    zip_iterator end() const {
        return {std::end(vec1), std::end(vec2)};
    }
};

int main() {
    std::vector<double> a{1., 2., 3.};
    std::vector<double> b{4., 5., 6.};

    zipper z{a, b};

    const auto add_product([](double sum, const auto& p){
        return sum + p.first * p.second;
    });

    const auto dot_product {std::accumulate(std::begin(z),
                              std::end(z),
                              0.0,
                              add_product)};

    std::cout << dot_product << std::endl;

    std::valarray<double> c{1., 2., 3.};
    std::valarray<double> d{4., 5., 6.};
    std::cout << (c * d).sum() << std::endl;
}