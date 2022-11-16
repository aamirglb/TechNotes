#include "database.hpp"
#include <stdexcept>

namespace Records {
Employee& Database::addEmployee(const std::string& firstName,
                                const std::string& lastName) {
    Employee e {firstName, lastName};
    e.setEmployeeNumer(m_nextEmployeeNumber++);
    e.hire();
    m_employees.push_back(e);
    return m_employees.back();
}

Employee& Database::getEmployee(int employeeNumber) {
    for(auto& employee : m_employees) {
        if(employee.getEmployeeNumber() == employeeNumber) {
            return employee;
        }
    }
    throw std::logic_error{ "No employee found." };
}

Employee& Database::getEmployee(const std::string& firstName,
                               const std::string& lastName) {
    for(auto& employee : m_employees) {
        if(employee.getFirstName() == firstName &&
            employee.getLastName() == lastName) {
            return employee;
        }
    }
    throw std::logic_error{ "No employee found." };
}

void Database::displayAll() const {
    for(const auto& employee : m_employees) {
        employee.display();
    }
}

void Database::displayCurrent() const {
    for(const auto& employee : m_employees) {
        if(employee.isHired()) {
            employee.display();
        }
    }
}

void Database::displayFormer() const {
    for(const auto& employee : m_employees) {
        if(!employee.isHired()) {
            employee.display();
        }
    }
}
}