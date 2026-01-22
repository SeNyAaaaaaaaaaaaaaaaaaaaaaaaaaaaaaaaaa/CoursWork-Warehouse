#include "Supplier.hpp"
#include <iostream>

Supplier::Supplier(string n, string cp, string ph, string em) : name(n), contactPerson(cp), phone(ph), email(em) {
}

void Supplier::display() const {
    cout << "================================" << endl;
    cout << "Поставщик: " << name << endl;
    cout << "Контактное лицо: " << contactPerson << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Email: " << email << endl;
    cout << "Товары: " << endl;

    for (int i = 0; i < products.size(); i++) {
        cout << "  " << i + 1 << ". " << products[i].getName() << " - "
            << products[i].getPrice() << " руб./" << products[i].getUnit() << endl;
    }
    cout << "================================" << endl;
}

void Supplier::addProduct(Product product) {
    products.push_back(product);
}

string Supplier::getName() const {
    return name;
}

vector<Product> Supplier::getProducts() const {
    return products;
}

Product Supplier::getProduct(int index) const {
    if (index >= 0 && index < products.size())
        return products[index];
    return Product();
}