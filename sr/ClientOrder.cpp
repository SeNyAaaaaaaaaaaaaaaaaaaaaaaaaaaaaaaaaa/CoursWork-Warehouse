#include "ClientOrder.hpp"
#include <iostream>

ClientOrder::ClientOrder(int i, Client c, Date sd) : id(i), client(c), shipmentDate(sd), isShipped(false), totalAmount(0) {orderDate = Date::getCurrentDate();}

void ClientOrder::display() const {
    cout << "================================" << endl;
    cout << "Заказ ID: " << id << endl;
    cout << "Клиент: " << client.getFullName() << endl;
    cout << "Компания: " << client.getCompanyName() << endl;
    cout << "Дата заказа: "; orderDate.display(); cout << endl;
    cout << "Дата отгрузки: "; shipmentDate.display(); cout << endl;
    cout << "Статус: " << (isShipped ? "Отгружен" : "Ожидает отгрузки") << endl;
    cout << "Товары: " << endl;


    for (int i = 0; i < products.size(); i++) {
        double cost = products[i].first.getPrice() * products[i].second;
        cout << "  " << i + 1 << ". " << products[i].first.getName()
            << " - " << products[i].second << " " << products[i].first.getUnit()
            << " - " << cost << " руб." << endl;
    }
    cout << "Сумма заказа: " << totalAmount << " руб." << endl;
    cout << "================================" << endl;
}

void ClientOrder::addProduct(Product product, int quantity) {
    products.push_back(make_pair(product, quantity));
    totalAmount += product.getPrice() * quantity;
}

void ClientOrder::shipOrder() {
    isShipped = true;
}

bool ClientOrder::getIsShipped() const {
    return isShipped;
}

int ClientOrder::getId() const {
    return id;
}

Date ClientOrder::getShipmentDate() const {
    return shipmentDate;
}

Client ClientOrder::getClient() const {
    return client;
}

vector<pair<Product, int>> ClientOrder::getProducts() const {
    return products;
}

double ClientOrder::getTotalAmount() const {
    return totalAmount;
}