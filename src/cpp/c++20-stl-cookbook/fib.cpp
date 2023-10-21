// fib.cpp : Generate list of fibonacci number 

#include <iostream>
#include <format>
#include <string>
#include <cstdint>
#include <stack>

struct Node {
    std::int8_t data;
    Node* next;

    Node( std::int8_t x ) {
        data = x;
        next = nullptr;
    }
};

class Number
{
private:
    Node *m_Head{};

public:
    Number() : m_Head{} {}

    // Store the input number in reverse order for easy calculation
    Number(const std::string& num) : m_Head{}
    {
        std::cout << "Constructing " << num << std::endl;
        for( size_t i = 0; i < num.size(); ++i)
        {
            Node* tmp = new Node( num[i] );
            if( m_Head != nullptr )
            {
                tmp->next = m_Head;
                m_Head = tmp;
            }
            else
            {
                m_Head = tmp;
            }
        }
    } 

    Number(const Number& rhs)
    {
        std::cout << "Copy Constructor: ";
        rhs.Display();
        std::cout << std::endl;

        auto curr = rhs.GetHead();

        while( curr != nullptr )
        {
            auto tmp = new Node(curr->data);
            if(m_Head != nullptr )
            {
                auto t = m_Head;
                while( t->next != nullptr ) t = t->next;
                t->next = tmp;
            }
            else
            {
                m_Head = tmp;
            }
            curr = curr->next;
        }
    }

    Number(Number&& rhs)
    {
        std::cout << "Move Constructor: ";
        rhs.Display();
        std::cout << std::endl;

        // Clear the source list before moving
        ClearNumber(m_Head);
        m_Head = rhs.m_Head;
        rhs.m_Head = nullptr;
    }

    Number& operator=(const Number& rhs)
    {
        std::cout << "Copy Assignment Operator: ";
        rhs.Display();
        std::cout << std::endl;

        if( *this == rhs )
        {
            return *this;
        }

        // delete the src list
        ClearNumber(m_Head);

        auto curr = rhs.GetHead();
        while( curr != nullptr )
        {
            auto tmp = new Node(curr->data);
            if( m_Head != nullptr )
            {
                auto t = m_Head;
                while( t->next != nullptr ) t = t->next;
                t->next = tmp;
            }
            else
            {
                m_Head = tmp;
            }
            curr = curr->next;
        }
        return *this;
    }

    Number& operator=(Number&& rhs)
    {
        std::cout << "Move Assignment operator: ";
        rhs.Display();
        std::cout << std::endl;

        // Clear the source list before moving
        ClearNumber(m_Head);
        m_Head = rhs.m_Head;
        rhs.m_Head = nullptr;
        return *this;
    }

    ~Number() 
    { 
        auto curr = m_Head;
        while(curr != nullptr)
        {
            auto tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        m_Head = nullptr;
    }

    void AddDigit(std::int8_t digit)
    {
        Node* tmp = new Node(digit);

        if( m_Head != nullptr )
        {
            // tmp->next = m_Head;
            // m_Head = tmp;
            auto t = m_Head;
            while(t->next != nullptr) t = t->next;
            t->next = tmp;
        }
        else
        {
            m_Head = tmp;
        }
    }

    void ClearNumber(Node*& head )
    {
        auto curr = head;
        while(curr != nullptr)
        {
            auto tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        head = nullptr;
    }

    void Display() const
    {
        std::stack<std::int8_t> stack;
        auto tmp = m_Head;

        while ( tmp != nullptr )
        {
            stack.push( tmp->data );
            tmp = tmp->next;
        }

        auto digits = stack.size();
        std::cout << " ( " << digits << " ): ";
        while ( !stack.empty() )
        {
            std::cout << stack.top();
            stack.pop();
        }
    }

    bool operator==(const Number& rhs)
    {
        return this->m_Head == rhs.m_Head;
    }

    const Node* GetHead() const { return m_Head; }
};


Number operator+(const Number& n1, const Number& n2)
{
    // std::cout << "Adding: ";
    // n1.Display();
    // std::cout << " + ";
    // n2.Display();
    // std::cout << "\n";

    // Add two number
    Number result{};
    auto h1 = n1.GetHead();
    auto h2 = n2.GetHead();
    int carry{};

    
    while ( h1 != nullptr && h2 != nullptr ) 
    {
        int sum = (h1->data - '0') + (h2->data - '0') + carry;
        int lastDigit = sum % 10;
        carry = sum / 10;
        result.AddDigit(lastDigit + '0');

        h1 = h1->next;
        h2 = h2->next;
    }

    while ( h1 != nullptr ) 
    {
        int sum = (h1->data - '0') + carry;
        int lastDigit = sum % 10;
        carry = sum / 10;
        result.AddDigit(lastDigit + '0');

        h1 = h1->next;
    }

    while ( h2 != nullptr ) 
    {
        int sum = (h2->data - '0') + carry;
        int lastDigit = sum % 10;
        carry = sum / 10;
        
        result.AddDigit(lastDigit + '0');

        h2 = h2->next;
    }
    if ( carry != 0 )
    {
        result.AddDigit(carry + '0');
    } 
    return result;
}


int main(int argc, char *argv[])
{
    int limit{2500};

    if(argc == 2)
    {
        limit = std::stoi(argv[1]);
    }

    Number n1("1");
    Number n2("1");
    Number n3{};

    for(int i = 0; i < limit; ++i)
    {
        std::cout << i+3 << ": ";
        n3 = n1 + n2;
        // n3.Display();
        // std::cout << std::endl;

        n1 = std::move(n2);
        n2 = std::move(n3);
    }
}