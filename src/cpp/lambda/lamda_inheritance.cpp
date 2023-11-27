#include <iostream>

template<typename Callable>
class ComplexFunctor : public Callable
{
public:
	explicit ComplexFunctor(Callable f) : Callable(f) {}
};

template <typename Callable>
ComplexFunctor<Callable> MakeComplexFunctor(Callable&& cal)
{
return ComplexFunctor<Callable>(cal);
}

int main()
{
	const auto func = MakeComplexFunctor([](){ std::cout << "Hello Functor!!"; });
	func();
}
