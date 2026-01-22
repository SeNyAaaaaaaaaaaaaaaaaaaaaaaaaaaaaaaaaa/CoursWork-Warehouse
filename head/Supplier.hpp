#pragma once
#include "Product.hpp"
#include <vector>
#include <string>
using namespace std;

class Supplier {
private:
    string name;
    string contactPerson;
    string phone;
    string email;
    vector<Product> products;

public:
    Supplier(string n = "", string cp = "", string ph = "", string em = "");
    void display() const;
    void addProduct(Product product);
    string getName() const;
    vector<Product> getProducts() const;
    Product getProduct(int index) const;
};