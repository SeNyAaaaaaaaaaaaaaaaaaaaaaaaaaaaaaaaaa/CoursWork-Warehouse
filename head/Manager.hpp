#pragma once
#include "Employee.hpp"
#include "Warehouse.hpp"
#include <memory>

class Manager : public Employee {
private:
    shared_ptr<Warehouse> warehouse;

public:
    Manager(string uname = "", string pwd = "", string name = "",string pos = "Manager", double sal = 0.0, Date hd = Date(),shared_ptr<Warehouse> w = nullptr);
    void showMenu() override;

private:
    void acceptSupply();
    void viewPendingSupplies();
    void hireEmployee();
    void fireEmployee();
    void viewEmployees();
    void setEmployeeSalary();
    void addToSchedule();
    void viewEmployeeSchedule();
};