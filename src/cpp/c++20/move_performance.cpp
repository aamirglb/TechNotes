#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std::string_literals;

class MyClass
{
private:
    std::vector<std::string> m_String{
        "This is a pretty long string that"
        " must be copy constructed into"
        " copyConstructed!"s
    };
    int m_Value{1};
public:
    MyClass() = default;
    MyClass(const MyClass& rhs) = default;
    MyClass(MyClass&& rhs) = default;

    int GetValue() const { return m_Value; }
};

int main()
{
    using MyVector = std::vector<MyClass>;
    constexpr unsigned int ITERATIONS{ 1000000U };

    MyVector copyConstruted(ITERATIONS);
    int value{};

    auto copyStartTime = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < ITERATIONS; ++i)
    {
        MyClass myclass;
        copyConstruted.push_back(myclass);
        value = myclass.GetValue();
    }
    auto copyEndTime = std::chrono::high_resolution_clock::now();

    MyVector moveConst(ITERATIONS);
    auto moveStartTiem = std::chrono::high_resolution_clock::now();
    for(auto i = 0; i < ITERATIONS; ++i)
    {
        MyClass myclass;
        moveConst.push_back(std::move(myclass));
        value = myclass.GetValue();
    }
    auto moveEndTime = std::chrono::high_resolution_clock::now();
    std::cout << value << std::endl;

    auto copyDuration = std::chrono::duration_cast<std::chrono::milliseconds>(copyEndTime - copyStartTime);
    std::cout << "Copy lasted: " << copyDuration.count() << " ms" << std::endl;

    auto moveDuration = std::chrono::duration_cast<std::chrono::milliseconds>(moveEndTime - moveStartTiem);
    auto percentage = static_cast<double>(moveDuration.count()) * 100. / static_cast<double>(copyDuration.count());
    std::cout << "Move lasted: " << moveDuration.count() << " ms (" << percentage << "%)" <<  std::endl;
}