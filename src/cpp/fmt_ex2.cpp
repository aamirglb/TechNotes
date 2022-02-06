#include <fmt/format.h>
#include <string>

using namespace std;

struct Employee {
	Employee(string_view firstName, string_view lastName, int32_t id)
		: m_firstName{firstName}
		, m_lastName{lastName}
		, m_empId{id}
	{
	}

	friend ostream& operator<<(ostream& out, const Employee& e) {
		out << e.m_firstName << " " << e.m_lastName << " (" << e.m_empId << ")\n";
	  	return out;	
	}

	private:
		string m_firstName;
		string m_lastName;
		int32_t m_empId;
};


int main() {
	int i {42};
	fmt::print("|{:5}|\n", i);
	fmt::print("|{:{}}|\n", i, 7);
    fmt::print("\n");

	fmt::print("|{:7}|\n", i);
	fmt::print("|{:<7}|\n", i);
	fmt::print("|{:_>7}|\n", i);
	fmt::print("|{:_^7}|\n", i);
    fmt::print("\n");

	fmt::print("|{:<5}|\n", i);
	fmt::print("|{:<+5}|\n", i);
	fmt::print("|{:< 5}|\n", i);
	fmt::print("|{:< 5}|\n", -i);
    fmt::print("\n");

	fmt::print("|{:10d}|\n", i);
	fmt::print("|{:10b}|\n", i);
	fmt::print("|{:#10b}|\n", i);
	fmt::print("|{:10X}|\n", i);
	fmt::print("|{:#10X}|\n", i);
    fmt::print("\n");

	string s { "ProCpp" };
	fmt::print("|{:_^10}|\n", s);
    fmt::print("\n");

	double d { 3.1415 / 2.3 };
	fmt::print("|{:12g}|\n", d);
	fmt::print("|{:12.2}|\n", d);
	fmt::print("|{:12e}|\n", d);

	int width{12};
	int precision {3};
	fmt::print("|{2:{0}.{1}f}|\n", width, precision, d);
	fmt::print("\n");

	fmt::print("|{:06d}|\n", i);
	fmt::print("|{:+06d}|\n", i);
	fmt::print("|{:06X}|\n", i);
	fmt::print("|{:#06X}|\n", i);
	fmt::print("\n");

	//fmt::print("{:.}\n", 5);
	Employee e("Aamir", "Ali", 421);
	fmt::print("{}\n", e);


}
