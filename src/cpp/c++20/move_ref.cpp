#include <iostream>

class MyClass
{
private:
    static int s_Counter;
    int* m_Member{ &s_Counter };
public:
    MyClass() 
    { 
        ++(*m_Member); 
        std::cout << "Constructing: " << GetValue() << std::endl;
    }

    ~MyClass() 
    { 
        if(m_Member)
        {
            --(*m_Member); 
            m_Member = nullptr;
            std::cout << "Destructing: " << s_Counter << std::endl;
        }
        else
        {
            std::cout << "Destroying a moved-from instance." << std::endl;
        }
    }

    MyClass(const MyClass& rhs) :
        m_Member{ rhs.m_Member }
    {
        ++(*m_Member);
        std::cout << "Copying: " << GetValue() << std::endl;
    }

    MyClass(MyClass&& rhs) : m_Member{ rhs.m_Member }
    {
        std::cout << std::hex << std::showbase;
        std::cout << "Moving: " << &rhs << " to " << this << std::endl;
        std::cout << std::noshowbase << std::dec;
        rhs.m_Member = nullptr;
    }
    int GetValue() const { return *m_Member; }
};

int MyClass::s_Counter{0};

MyClass CopyMyClass(MyClass param)
{
    return param;
}

int main()
{
    auto obj1 = MyClass();
    
    {
        auto obj2 = MyClass();
    }

    auto obj3 = MyClass();
    auto obj4 = CopyMyClass(obj3);
}