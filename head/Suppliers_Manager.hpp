#pragma once
#include "Supplier.hpp"
#include <map>
#include <memory>

class SupplierManager {
private:
    map<int, unique_ptr<Supplier>> suppliers; 
    int next_supplier_id = 1;
public:
    Supplier* createSupplier(string name, string description, string contact);
    Supplier* findSupplier(int supplier_id) const;
    bool removeSupplier(int supplier_id);
    void displayAllSuppliers() const;
};