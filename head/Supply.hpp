#pragma once
#include "Supplier.hpp"
#include "Product.hpp"
#include "Date.hpp"
#include <vector>
#include <utility>
#include <string>
using namespace std;

class Supply {
private:
    int id;
    Supplier supplier;
    vector<pair<Product, int>> products;
    Date deliveryDate;
    Date acceptanceDate;
    bool isAccepted;
    string administrator;

public:
    Supply(int i = 0, Supplier s = Supplier(), Date dd = Date());
    void display() const;
    void addProduct(Product product, int quantity);
    void acceptSupply();
    bool getIsAccepted() const;
    int getId() const;
    Date getDeliveryDate() const;
    vector<pair<Product, int>> getProducts() const;
    Supplier getSupplier() const;
    void setAdministrator(string admin);
};