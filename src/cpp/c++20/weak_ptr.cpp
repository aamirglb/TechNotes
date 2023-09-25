#include <iostream>
#include <memory>

using namespace std;

class MyClass
{
private:
    std::string m_Name;
    int m_Value;
public:
    MyClass (const std::string& name, int value) :
        m_Name{name},
        m_Value{value}
    {
        std::cout << "Constructing!" << std::endl;
    }

    ~MyClass()
    {
        std::cout << "Destructing!" << std::endl;
    }

    const std::string& GetName() const
    {
        return m_Name;
    }

    int GetValue() const
    {
        return m_Value;
    }
};

auto PassSharedPtr(std::shared_ptr<MyClass> ptr)
{
    std::cout << "In function Name: " << ptr->GetName() << std::endl;
    return ptr;
}

int main()
{
    std::weak_ptr<MyClass> weakPtr;
    {
        auto sharedPtr = std::make_shared<MyClass>("MyClass", 10);
        weakPtr = sharedPtr;
        {
            auto newSharedPtr = PassSharedPtr(sharedPtr);
            if(sharedPtr)
            {
                std::cout << "First object name: " << sharedPtr->GetName() << std::endl;
            }
            std::cout << "Second object name: " << newSharedPtr->GetName() << std::endl;

            auto sharedFromWeak1 = weakPtr.lock();
            if( sharedFromWeak1)
            {
                std::cout << "Name from weak1: " << sharedFromWeak1->GetName() << std::endl;
            }

        }
    }

    auto sharedFromWeak2 = weakPtr.lock();
    if(!sharedFromWeak2)
    {
        std::cout << "Shared pointer out of scope!!" << std::endl;
    }
}