#include <iostream>

class Base {
public:
    void foo() {
        std::cout << "foo called\n";
    }

    ~Base() {
        std::cout << "Base destructor called\n";
    }
};

class Derived : public Base {
public:
    ~Derived() {
        std::cout << "Derived destructor called\n";
    }

    void bar() {
        std::cout << "bar called\n";
    }
};

int main() {
    {
        Base *ptr = new Derived;
        ptr->foo();
        delete ptr;
    }
}