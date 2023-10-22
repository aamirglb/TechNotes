#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <array>

enum class Type {
    TYPE_A,
    TYPE_B,
    TYPE_C
};

class Test
{
public:
    void FunA() { std::cout << "function A\n"; }
    void FunB() { std::cout << "function B\n"; }
    void FunC() { std::cout << "function C\n"; }

};


int main()
{
    using MediaListBuilder = std::function<void(Test&)>;
    std::map<Type, MediaListBuilder> MediaListBuilderTable;

	std::array<Type, 3> a{ Type::TYPE_B, Type::TYPE_C, Type::TYPE_A };
    MediaListBuilderTable[Type::TYPE_A] = &Test::FunA;
    MediaListBuilderTable[Type::TYPE_B] = &Test::FunB;
    MediaListBuilderTable[Type::TYPE_C] = &Test::FunC;

    Test test;
	for(const auto& t : a)
	{
		MediaListBuilderTable[t](test);
	}
}
