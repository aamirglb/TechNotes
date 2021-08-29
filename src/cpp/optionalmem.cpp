#include <string>
#include <optional>
#include <iostream>

class Name {
private:
    std::string first;
    std::optional<std::string> middle;
    std::string last;
public:
    Name(std::string f, 
        std::optional<std::string> m,
        std::string l) 
    : first{std::move(f)}, middle{std::move(m)}, last{std::move(l)} {

    }

    friend std::ostream& operator << (std::ostream& strm, const Name& n) {
        strm << n.first << ' ';
        if(n.middle) {
            strm << *n.middle << ' ';
        }
        return strm << n.last;
    }
};

int main() {
    Name n{"Aamir", std::nullopt, "Ali"};
    std::cout << n << '\n';

    Name m{"Mohammad", "Aamir", "Ali"};
    std::cout << m << '\n';
}