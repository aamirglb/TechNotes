struct MyClass
{
	MyClass(char c) : MyClass { 1.2 } { }
	MyClass(double d) : MyClass { 'm' } { }
};

int main() {
	MyClass c { 1. };
}
