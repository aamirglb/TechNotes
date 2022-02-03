#include <fmt/format.h>

struct Employee {
	char firstInitial;
	char lastInitial;
	int employeeNumber;
	int salary { 75'000 };

	void display() const {
		fmt::print("{} {}, {}, {}\n",
				firstInitial,
				lastInitial,
				employeeNumber,
				salary);
	}
};

int main() {
	// designated initializer
	Employee jd {
		.firstInitial = 'J',
		.lastInitial = 'D',
//		.employeeNumber = 42,
		.salary = 80'000
	};

	jd.display();
}
