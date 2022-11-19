#include "format"

class Base
{
public:
    Base() {}
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    Derived()
    {
        m_string = new char[30];
        fmt::print("m_string allocated\n");
    }

    ~Derived()
    {
        delete[] m_string;
        fmt::print("m_string deallocated\n");
    }
private:
    char* m_string;
};

class Base1
{
public:
    virtual ~Base1() = default;
    virtual void someMethod()
    {
        fmt::print("Base::{}\n", __func__);
    }
};

class Derived1 : public Base1
{
public:
    void someMethod() override /*final*/
    {
        fmt::print("Derived1::{}\n", __func__);
    }
};

class DDerived1 : public Derived1
{
public:
    void someMethod() override
    {
        fmt::print("DDerived1::{}\n", __func__);
    }
};


int main()
{
    Base *ptr { new Derived };
    delete ptr;

    Base1 *p2 { new DDerived1{} };
    p2->someMethod();
}