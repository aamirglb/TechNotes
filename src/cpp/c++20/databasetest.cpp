#include "format"
#include "database.hpp"

using namespace Records;

int main() {
    Database db;
    Employee& e1 {db.addEmployee("Aamir", "Ali") };
    e1.fire();

    Employee& e2 { db.addEmployee("Ahmed", "Ali")};
    e2.setSalary(100'000);

    Employee& e3 { db.addEmployee("Umar", "Farooq") };
    e3.setSalary(10'000);
    e3.promote();

    fmt::print("All Employees: \n\n");
    db.displayAll();

    fmt::print("\n\nCurrent Employees: \n\n");
    db.displayCurrent();

    fmt::print("\n\nFormer Employees: \n\n");
    db.displayFormer();
}