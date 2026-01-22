#pragma once
#include "Product.hpp"
#include "Addressing.hpp"
#include "Supply.hpp"
#include "ClientOrder.hpp"
#include "Date.hpp"
#include <vector>
#include <string>
#include <utility>
#include <memory>
using namespace std;

class Warehouse {
private:
    struct WarehouseItem {
        Product product;
        int quantity;
        Addressing address;
        Date arrivalDate;
    };

    vector<WarehouseItem> inventory;
    vector<Supply> pendingSupplies;
    vector<ClientOrder> pendingOrders;
    string name;
    string address;

public:
    Warehouse(string n = "Главный склад", string addr = "");
    void addFromSupply(Supply& supply);
    bool shipFromOrder(ClientOrder& order);
    void displayInventory() const;
    void addPendingSupply(Supply supply);
    void addPendingOrder(ClientOrder order);
    vector<Supply>& getPendingSupplies();
    vector<ClientOrder>& getPendingOrders();
    vector<WarehouseItem> getInventory() const;
    Product getProductByName(string name);
    string getName() const;
    string getAddress() const;
};