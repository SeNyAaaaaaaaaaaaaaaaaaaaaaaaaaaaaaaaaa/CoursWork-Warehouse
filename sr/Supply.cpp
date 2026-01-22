#include "Supply.hpp"
#include <iostream>
#include <iomanip>

Supply::Supply(int i, Supplier s, Date dd) : id(i), supplier(s), deliveryDate(dd), isAccepted(false) {}

void Supply::display() const {
    cout << "================================" << endl;
    cout << "Поставка ID: " << id << endl;
    cout << "Поставщик: " << supplier.getName() << endl;
    cout << "Дата доставки: "; deliveryDate.display(); cout << endl;
    cout << "Статус: " << (isAccepted ? "Принята" : "Ожидает приемки") << endl;
    if (isAccepted) {
        cout << "Дата приемки: "; acceptanceDate.display(); cout << endl;
    }
    cout << "Товары: " << endl;

    double total = 0;
    for (int i = 0; i < products.size(); i++) {
        double cost = products[i].first.getPrice() * products[i].second;
        total += cost;
        cout << "  " << i + 1 << ". " << products[i].first.getName()
            << " - " << products[i].second << " " << products[i].first.getUnit()
            << " - " << cost << " руб." << endl;
    }
    cout << "Итого: " << total << " руб." << endl;
    cout << "================================" << endl;
}

void Supply::addProduct(Product product, int quantity) {
    products.push_back(make_pair(product, quantity));
}

void Supply::acceptSupply() {
    isAccepted = true;
    acceptanceDate = Date::getCurrentDate();
}

bool Supply::getIsAccepted() const {
    return isAccepted;
}

int Supply::getId() const {
    return id;
}

Date Supply::getDeliveryDate() const {
    return deliveryDate;
}

vector<pair<Product, int>> Supply::getProducts() const {
    return products;
}

Supplier Supply::getSupplier() const {
    return supplier;
}

void Supply::setAdministrator(string admin) {
    administrator = admin;
}