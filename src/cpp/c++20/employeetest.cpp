#include "employee.hpp"
#include "format"

using namespace Records;

int main() {
    fmt::print("Testing the Employee Class.\n");

    Employee e1 {"Aamir", "Ali"};
    e1.setEmployeeNumer(286);
    e1.setSalary(31'380);
    e1.promote();
    e1.promote(50);
    e1.hire();
    e1.display();
}