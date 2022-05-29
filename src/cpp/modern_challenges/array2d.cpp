#include <initializer_list>
#include <vector>
#include <iostream>
#include <iterator>

template <typename T, size_t R, size_t C>
class array2d
{
private:
    // typedef T                   value_type;
    // typedef value_type*         iterator;
    // typedef value_type const*   const_iterator;

    using value_type = T;
    using iterator = value_type*;
    using const_iterator = const value_type*;
    std::vector<T>              arr;
public:
    array2d() : arr(R*C) {}
    explicit array2d(std::initializer_list<T> list) : arr(list) {}

    constexpr T* data() noexcept {
        return arr.data();
    }

    constexpr const T* data() const noexcept {
        return arr.data();
    }

    constexpr T& at(const size_t r, const size_t c) {
        return arr.at(r*C + c);
    }

    constexpr const T& at(const size_t r, const size_t c) const {
        return arr.at(r*C + c);
    }

    constexpr T& operator()(const size_t r, const size_t c) {
        return arr[r*C + c];
    }

    constexpr const T& operator()(const size_t r, const size_t c) const {
        return arr[r*C + c];
    }

    constexpr bool empty() const noexcept {
        return R == 0 || C == 0;
    }

    constexpr size_t size(int const rank) const {
        if(rank == 1) return R;
        else if (rank == 2) return C;
        throw std::out_of_range("Rank is out of range!");
    }

    void fill(const T& value) {
        std::fill(std::begin(arr), std::end(arr), value);
    }

    void auto_fill(T start_value, T step = 1) {
        for(size_t i = 0; i < arr.size(); ++i) {
            arr[i] = start_value;
            start_value += step;
        }
    }

    void swap(array2d &other) noexcept {
        arr.swap(other.arr);
    }

    friend std::ostream& operator<<(std::ostream& os, array2d a) {
        for(size_t i = 0; i < a.arr.size() - 1; ++i) {
            os << a.arr[i] << ", ";
        }
        os << a.arr[ a.arr.size() - 1] << "\n";
        return os;
    }

    const_iterator begin() const { return arr.data(); }
    const_iterator end() const { return arr.data() + arr.size(); }
    iterator       begin() { return arr.data(); }
    iterator       end() { return arr.data() + arr.size(); }
};

int main()
{
    array2d<int32_t, 2, 3> a{1, 2, 3, 4, 5, 6};
    std::cout << a;

    for(size_t r = 0; r < a.size(1); ++r) {
        for(size_t c = 0; c < a.size(2); ++c) {
            a(r, c) *= 2;
        }
    }
    std::cout << a;

    std::copy(std::begin(a), std::end(a),
        std::ostream_iterator<int32_t>(std::cout, " "));
    std::cout << std::endl;

    array2d<int32_t, 4, 3> b;
    b.fill(2);

    std::cout << "b: ";
    std::cout << b;

    array2d<int32_t, 4, 3> c;
    c.fill(3);
    std::cout << "c: " << c;

    b.auto_fill(0, 10);
    std::cout << "b: " << b;

    c.auto_fill(0);
    std::cout << "c: " << c;

    array2d<double, 2, 5> d;
    d.auto_fill(0, 0.1);
    std::cout << "d: " << d;

}