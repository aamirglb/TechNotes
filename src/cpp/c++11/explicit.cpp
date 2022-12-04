#include <iostream>

class Foo {
public:
    Foo(int x) : x_{x} {
        std::cout << "Foo(" << x_ << ")\n";
    }
    operator int() { return x_; }
    int x_;
};

class Bar {
public:
    explicit Bar(double x) : x_ {x} {
        std::cout << "Bar(" << x_ << ")\n";
    }
    explicit operator double() { return x_; }
    double x_;
};


class Baz {
public:
    Baz(double x) { std::cout << "Baz(double)\n"; }
    explicit Baz(bool x) { std::cout << "Baz(bool)\n"; }
    operator double() { std::cout << "operator double()\n"; }
    explicit operator bool() { std::cout << "operator bool()\n"; }
};

int main() {
    Foo a = 42;
    Foo b(43);
    Foo c = Foo(44);
    Foo d = (Foo)45;
    int e = d;

    // Bar x = 3.14;   // Error
    Bar y(3.14);
    Bar z = Bar(3.14);
    Bar w = (Bar)3.14;
    // double v = w;   // Error
    double u = double(w);

    Baz i = true;  // implicit converstion from bool to double
    Baz j = Baz(true);
    double k = j;
    bool l = j;

}