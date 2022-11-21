#include "format"
#include <string>
#include <bit>

class Book
{
public:
    virtual ~Book() = default;
    virtual std::string getDescription() const { return "Book"; }
    virtual int getHeight() const { return 120; }
};

class Paperback : public Book
{
public:
    std::string getDescription() const override {
        return "Paperback " + Book::getDescription();
    }
};

class Romance : public Paperback
{
public:
    std::string getDescription() const override {
        return "Romance " + Paperback::getDescription();
    }
    int getHeight() const override {
        return Paperback::getHeight() / 2;
    }
};

class Technical : public Book
{
public:
    std::string getDescription() const override {
        return "Technical " + Book::getDescription();
    }
};

class Dog
{
public:
    virtual void bark() { fmt::print("Woof!\n"); }
    virtual void eat() { fmt::print("The dog ate.\n"); }
};

class Bird
{
public:
    virtual void chirp() { fmt::print("Chirp!\n"); }
    virtual void eat() { fmt::print("The bird ate.\n"); }
};

class DogBird : public Dog, public Bird
{
public:
    virtual void eat() { fmt::print("DogBird ate.\n"); }
};

class Base
{
public:
    virtual ~Base() = default;
    Base(std::string_view str) : m_str { str }
    {}
private:
    std::string m_str;
};

class Derived : public Base
{
public:
    using Base::Base;
    Derived(int i) : Base {""}, m_int{i}
    {}
    void show() { fmt::print("m_int = {}\n", m_int); }

private:
    int m_int;
};


int main()
{
    Romance novel;
    Book book;
    fmt::print("{}\n", novel.getDescription());
    fmt::print("{}\n", book.getDescription());
    fmt::print("{}\n", novel.getHeight());
    fmt::print("{}\n", book.getHeight());

    DogBird db;
    db.eat();
    // db.DogBird::eat();
    // db.Dog::eat();

    Derived s1 {2};
    Derived s2 {"Hello World"};
    s1.show();
    s2.show();

    fmt::print("\n\n");

    float f { 1.23f };
    auto i { std::bit_cast<unsigned int>(f) };
    fmt::print("{:x}, {}\n", i, i);
}
