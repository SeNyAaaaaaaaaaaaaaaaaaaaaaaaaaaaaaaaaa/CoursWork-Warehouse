#include "ClientRole.hpp"
#include "GlobalData.hpp"
#include <iostream>
#include <limits>
#include <memory>

ClientRole::ClientRole(Client u, shared_ptr<Warehouse> w) : user(u), warehouse(w) {}

void ClientRole::showMenu() {
    int choice;
    do {
        try {
            cout << "\n================================" << endl;
            cout << "РЕЖИМ КЛИЕНТА" << endl;
            cout << "Клиент: " << user.getFullName() << endl;
            cout << "Компания: " << user.getCompanyName() << endl;
            cout << "================================" << endl;
            cout << "1. Просмотреть товары на складе" << endl;
            cout << "2. Создать новый заказ" << endl;
            cout << "3. Просмотреть мои заказы" << endl;
            cout << "4. Просмотреть информацию о себе" << endl;
            cout << "0. Выход" << endl;
            cout << "Выбор: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Неверный ввод. Введите число.");
            }

            switch (choice) {
            case 1: viewWarehouseProducts(); break;
            case 2: createOrder(); break;
            case 3: viewMyOrders(); break;
            case 4: user.displayInfo(); break;
            case 0: cout << "Выход из режима клиента..." << endl; break;
            default: cout << "Неверный выбор!" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
        catch (...) {
            cout << "Неизвестная ошибка!" << endl;
        }
    } while (choice != 0);
}

void ClientRole::viewWarehouseProducts() {
    try {
        if (warehouse) {
            warehouse->displayInventory();
        }
        else {
            cout << "Ошибка: склад недоступен!" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре товаров: " << e.what() << endl;
    }
}

void ClientRole::createOrder() {
    try {
        if (!warehouse) {
            throw runtime_error("Склад недоступен!");
        }

        warehouse->displayInventory();

        int day, month, year;
        cout << "\nСоздание нового заказа" << endl;
        cout << "Введите желаемую дату отгрузки (день месяц год): ";
        cin >> day >> month >> year;

        if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 2023) {
            throw runtime_error("Некорректная дата!");
        }

        Date shipmentDate(day, month, year);

        int nextId = 1;
        vector<ClientOrder> allOrders = GlobalData::getInstance()->getClientOrders();
        if (!allOrders.empty()) {
            for (const auto& order : allOrders) {
                if (order.getId() >= nextId) {
                    nextId = order.getId() + 1;
                }
            }
        }

        ClientOrder newOrder(nextId, user, shipmentDate);

        char addMore = 'y';
        do {
            string productName;
            int quantity;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Введите наименование товара: ";
            getline(cin, productName);
            cout << "Введите количество: ";
            cin >> quantity;

            if (quantity <= 0) {
                throw runtime_error("Количество должно быть положительным!");
            }

            Product product = warehouse->getProductByName(productName);
            if (product.getName() != "") {
                newOrder.addProduct(product, quantity);
                cout << "Товар добавлен в заказ!" << endl;
            }
            else {
                cout << "Товар не найден на складе!" << endl;
            }

            cout << "\nДобавить еще товар? (y/n): ";
            cin >> addMore;

        } while (addMore == 'y' || addMore == 'Y');

        if (newOrder.getProducts().empty()) {
            throw runtime_error("Заказ не может быть пустым!");
        }

        GlobalData::getInstance()->addClientOrder(newOrder);
        warehouse->addPendingOrder(newOrder);

        Client* clientPtr = GlobalData::getInstance()->getClientByUsername(user.getUsername());
        if (clientPtr) {
            clientPtr->addOrder(newOrder.getId());
        }

        cout << "\nЗаказ создан успешно! ID: " << newOrder.getId() << endl;
        cout << "Сумма заказа: " << newOrder.getTotalAmount() << " руб." << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при создании заказа: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void ClientRole::viewMyOrders() {
    try {
        vector<ClientOrder> myOrders = GlobalData::getInstance()->getClientOrdersByUsername(user.getUsername());

        if (myOrders.empty()) {
            cout << "У вас нет заказов!" << endl;
            return;
        }

        cout << "\nМОИ ЗАКАЗЫ:" << endl;
        for (auto& order : myOrders) {
            order.display();
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре заказов: " << e.what() << endl;
    }
}