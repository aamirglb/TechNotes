#include <stdexcept>
#include <exception>
#include <string>
#include <iostream>
#include "format"
#include "employee.hpp"
#include "database.hpp"

using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);

int main() {
    Database employeeDB;
    bool done{};

    while(!done) {
        int selection{displayMenu()};

        switch(selection) {
        case 0:
            done = true;
            break;
        case 1:
            doHire(employeeDB);
            break;
        case 2:
            doFire(employeeDB);
            break;
        case 3:
            doPromote(employeeDB);
            break;
        case 4:
            employeeDB.displayAll();
            break;
        case 5:
            employeeDB.displayCurrent();
            break;
        case 6:
            employeeDB.displayFormer();
            break;
        default:
            fmt::print(std::cerr, "Unknown command.\n");
            break;
        }

        // if(selection != 0) {
        //     std::cin.ignore();
        //     fmt::print("\nPress Enter key to continue...");
        //     std::string s;
        //     std::getline(std::cin, s);
        // }
    }
}

int displayMenu() {
    int selection;
    fmt::print("\n");
    fmt::print("Employee Database\n");
    fmt::print("------------------\n");
    fmt::print("1) Hire a new employee\n");
    fmt::print("2) Fire an employee\n");
    fmt::print("3) Promote an employee\n");
    fmt::print("4) List all employees\n");
    fmt::print("5) List all current employees\n");
    fmt::print("6) List all former employees\n");
    fmt::print("0) Quit\n\n");
    fmt::print("---> ");
    std::cin >> selection;
    return selection;
}

void doHire(Database& db) {
    std::string firstName, lastName;
    fmt::print("First name? ");
    std::cin >> firstName;

    fmt::print("Last Name? ");
    std::cin >> lastName;

    auto& employee {db.addEmployee(firstName, lastName)};
    fmt::print("Hired employee {} {} with employee number {}.\n",
        firstName, lastName, employee.getEmployeeNumber());
}

void doFire(Database& db) {
    int employeeNum;
    fmt::print("Employee Number? ");
    std::cin >> employeeNum;

    try {
        auto& emp {db.getEmployee(employeeNum)};
        emp.fire();
        fmt::print("Employee {} terminated.\n", employeeNum);
    } catch(const std::logic_error& e) {
        fmt::print(std::cerr, "Unable to termniate employee: {}\n",
            e.what());
    }
}

void doPromote(Database& db) {
    int employeeNum;
    fmt::print("Employee Number? ");
    std::cin >> employeeNum;

    int raiseAmount;
    fmt::print("How much of a raise? ");
    std::cin >> raiseAmount;

    try {
        auto& emp{db.getEmployee(employeeNum)};
        emp.promote(raiseAmount);
    } catch(const std::logic_error& e) {
        fmt::print(std::cerr, "Unable to promote employee: {}\n",
            e.what());
    }

}

