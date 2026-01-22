#pragma once
#include "Employee.hpp"
#include "Warehouse.hpp"
#include <memory>

class StoreKeeper : public Employee {
private:
    shared_ptr<Warehouse> warehouse;

public:
    StoreKeeper(string uname = "", string pwd = "", string name = "",string pos = "StoreKeeper", double sal = 0.0, Date hd = Date(),shared_ptr<Warehouse> w = nullptr);
    void showMenu() override;

private:
    void viewPendingOrders();
    void shipOrder();
};