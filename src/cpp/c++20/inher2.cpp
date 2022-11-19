#include "format"
#include <string>

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

int main()
{
    Romance novel;
    Book book;
    fmt::print("{}\n", novel.getDescription());
    fmt::print("{}\n", book.getDescription());
    fmt::print("{}\n", novel.getHeight());
    fmt::print("{}\n", book.getHeight());
}