#include "Warehouse.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

Warehouse::Warehouse(string n, string addr) : name(n), address(addr) {srand(time(0));}

void Warehouse::addFromSupply(Supply& supply) {
    if (!supply.getIsAccepted()) {
        cout << "Поставка не принята менеджером!" << endl;
        return;
    }

    vector<pair<Product, int>> products = supply.getProducts();

    cout << "\nДобавление товаров из поставки:" << endl;
    for (auto& item : products) {
        bool found = false;
        for (auto& invItem : inventory) {
            if (invItem.product.getName() == item.first.getName()) {
                invItem.quantity += item.second;
                found = true;
                cout << "  + " << item.second << " " << item.first.getUnit()
                    << " " << item.first.getName()
                    << " (теперь: " << invItem.quantity << ")" << endl;
                break;
            }
        }

        if (!found) {
            WarehouseItem newItem;
            newItem.product = item.first;
            newItem.quantity = item.second;
            newItem.address = Addressing("A", rand() % 10 + 1, rand() % 5 + 1, rand() % 20 + 1);
            newItem.arrivalDate = Date::getCurrentDate();
            inventory.push_back(newItem);

            cout << "  + Новый товар: " << item.second << " "
                << item.first.getUnit() << " " << item.first.getName()
                << " по адресу: ";
            newItem.address.display();
        }
    }

    cout << "Товары из поставки успешно добавлены на склад!" << endl;
}

bool Warehouse::shipFromOrder(ClientOrder& order) {
    vector<pair<Product, int>> orderProducts = order.getProducts();

    cout << "\nОтгрузка заказа ID " << order.getId() << ":" << endl;

    for (auto& orderItem : orderProducts) {
        bool hasEnough = false;
        for (auto& invItem : inventory) {
            if (invItem.product.getName() == orderItem.first.getName() &&
                invItem.quantity >= orderItem.second) {
                hasEnough = true;
                break;
            }
        }
        if (!hasEnough) {
            cout << "Недостаточно товара: " << orderItem.first.getName()
                << " (нужно: " << orderItem.second << ", есть: ";
            for (auto& invItem : inventory) {
                if (invItem.product.getName() == orderItem.first.getName()) {
                    cout << invItem.quantity << ")" << endl;
                    break;
                }
            }
            cout << "  Отгрузка отменена!" << endl;
            return false;
        }
    }

    for (auto& orderItem : orderProducts) {
        for (auto& invItem : inventory) {
            if (invItem.product.getName() == orderItem.first.getName()) {
                int oldQuantity = invItem.quantity;
                invItem.quantity -= orderItem.second;
                cout << "  - " << orderItem.second << " " << orderItem.first.getUnit()
                    << " " << orderItem.first.getName()
                    << " (было: " << oldQuantity << ", стало: " << invItem.quantity << ")" << endl;
                break;
            }
        }
    }

    order.shipOrder();
    cout << "Заказ успешно отгружен!" << endl;
    return true;
}

void Warehouse::displayInventory() const {
    cout << "================================" << endl;
    cout << "СКЛАД: " << name << endl;
    cout << "ИНВЕНТАРЬ:" << endl;
    cout << "================================" << endl;

    if (inventory.empty()) {
        cout << "Склад пуст!" << endl;
    }
    else {
        double totalValue = 0;
        for (int i = 0; i < inventory.size(); i++) {
            const auto& item = inventory[i];
            double value = item.product.getPrice() * item.quantity;
            totalValue += value;

            cout << i + 1 << ". " << item.product.getName() << endl;
            cout << "   Категория: " << item.product.getCategory() << endl;
            cout << "   Количество: " << item.quantity << " " << item.product.getUnit() << endl;
            cout << "   Цена за ед.: " << item.product.getPrice() << " руб." << endl;
            cout << "   Общая стоимость: " << value << " руб." << endl;
            cout << "   Адрес: "; item.address.display();
            cout << "   Дата поступления: "; item.arrivalDate.display(); cout << endl;
            cout << "   -------------------------" << endl;
        }
        cout << "Общая стоимость инвентаря: " << totalValue << " руб." << endl;
    }
    cout << "================================" << endl;
}

void Warehouse::addPendingSupply(Supply supply) {
    pendingSupplies.push_back(supply);
}

void Warehouse::addPendingOrder(ClientOrder order) {
    pendingOrders.push_back(order);
}

vector<Supply>& Warehouse::getPendingSupplies() {
    return pendingSupplies;
}

vector<ClientOrder>& Warehouse::getPendingOrders() {
    return pendingOrders;
}

vector<Warehouse::WarehouseItem> Warehouse::getInventory() const {
    return inventory;
}

Product Warehouse::getProductByName(string name) {
    for (const auto& item : inventory) {
        if (item.product.getName() == name) {
            return item.product;
        }
    }
    return Product();
}

string Warehouse::getName() const {
    return name;
}

string Warehouse::getAddress() const {
    return address;
}