#pragma once
#include "Client.hpp"
#include "Product.hpp"
#include "Date.hpp"
#include <vector>
#include <utility>
#include <string>
using namespace std;

class ClientOrder {
private:
    int id;
    Client client;
    vector<pair<Product, int>> products;
    Date orderDate;
    Date shipmentDate;
    bool isShipped;
    double totalAmount;

public:
    ClientOrder(int i = 0, Client c = Client(), Date sd = Date());
    void display() const;
    void addProduct(Product product, int quantity);
    void shipOrder();
    bool getIsShipped() const;
    int getId() const;
    Date getShipmentDate() const;
    Client getClient() const;
    vector<pair<Product, int>> getProducts() const;
    double getTotalAmount() const;
};