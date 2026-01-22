#pragma once
#include <string>
using namespace std;

class Product {
private:
    string name;
    string category;
    string unit;
    double price;
    string specifications;

public:
    Product(string n = "", string cat = "", string u = "רע.", double p = 0.0, string spec = "");
    void display() const;
    string getName() const;
    string getCategory() const;
    string getUnit() const;
    double getPrice() const;
    string getSpecifications() const;
    void setPrice(double p);
};