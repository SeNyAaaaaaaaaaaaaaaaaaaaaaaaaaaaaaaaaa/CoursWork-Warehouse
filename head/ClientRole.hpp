#pragma once
#include "Client.hpp"
#include "Warehouse.hpp"
#include "ClientOrder.hpp"
#include <vector>
#include <memory>
using namespace std;

class ClientRole {
private:
    Client user;
    shared_ptr<Warehouse> warehouse;
    vector<ClientOrder> myOrders;

public:
    ClientRole(Client u, shared_ptr<Warehouse> w);
    void showMenu();

private:
    void viewWarehouseProducts();
    void createOrder();
    void viewMyOrders();
};