#pragma once
#include "Employee.hpp"
#include "Supplier.hpp"
#include "Supply.hpp"
#include <vector>
#include <memory>
using namespace std;

class Administrator : public Employee {
private:
    vector<Supplier> suppliers;
    vector<Supply> createdSupplies;

public:
    Administrator(string uname = "", string pwd = "", string name = "",string pos = "Admin", double sal = 0.0, Date hd = Date());

    void showMenu() override;

private:
    void addSupplier();
    void viewSuppliers();
    void createSupply();
    void viewCreatedSupplies();
    void viewSupplierProducts();
};