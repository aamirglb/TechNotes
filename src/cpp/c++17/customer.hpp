#include <string>
#include <utility>

class Customer {
public:
    Customer(std::string f, std::string l, long v)
        : first{std::move(f)}
        , last{std::move(l)}
        , val{v}
    {}

    std::string getFirst() const {
        return first;
    }

    std::string getLast() const {
        return last;
    }

    long getValue() const {
        return val;
    }

    const std::string& firstname() const {
        return first;
    }

    std::string& firstname() {
        return first;
    }

    const std::string& lastname() const {
        return last;
    }

    std::string& lastname() {
        return last;
    }

    long value() const {
        return val;
    }

    long& value() {
        return val;
    }
private:
    std::string first;
    std::string last;
    long val;
};

