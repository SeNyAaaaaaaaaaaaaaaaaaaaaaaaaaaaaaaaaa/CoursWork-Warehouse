#include "StoreKeeper.hpp"
#include "GlobalData.hpp"
#include <iostream>
#include <limits>
#include <memory>
using namespace std;

StoreKeeper::StoreKeeper(string uname, string pwd, string name,string pos, double sal, Date hd,shared_ptr<Warehouse> w): Employee(uname, pwd, name, pos, sal, hd), warehouse(w) {}

void StoreKeeper::showMenu() {
    int choice;
    do {
        try {
            cout << "\n================================" << endl;
            cout << "РЕЖИМ КЛАДОВЩИКА" << endl;
            cout << "Кладовщик: " << getFullName() << endl;
            cout << "================================" << endl;
            cout << "1. Просмотреть заказы на отгрузку" << endl;
            cout << "2. Отгрузить заказ" << endl;
            cout << "3. Просмотреть текущий инвентарь" << endl;
            cout << "0. Выход" << endl;
            cout << "Выбор: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Неверный ввод. Введите число.");
            }

            switch (choice) {
            case 1: viewPendingOrders(); break;
            case 2: shipOrder(); break;
            case 3: if (warehouse) warehouse->displayInventory(); break;
            case 0: cout << "Выход из режима кладовщика..." << endl; break;
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

void StoreKeeper::viewPendingOrders() {
    try {
        vector<ClientOrder> pendingOrders = GlobalData::getInstance()->getPendingClientOrders();
        Date currentDate = Date::getCurrentDate();

        if (pendingOrders.empty()) {
            cout << "Нет заказов на отгрузку!" << endl;
            return;
        }

        cout << "\nЗАКАЗЫ НА ОТГРУЗКУ:" << endl;
        for (int i = 0; i < pendingOrders.size(); i++) {
            if (!pendingOrders[i].getIsShipped()) {
                cout << i + 1 << ". ";
                pendingOrders[i].display();

                if (pendingOrders[i].getShipmentDate() == currentDate) {
                    cout << "!!! СЕГОДНЯ ДЕНЬ ОТГРУЗКИ !!!" << endl;
                }
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре заказов: " << e.what() << endl;
    }
}

void StoreKeeper::shipOrder() {
    try {
        vector<ClientOrder> pendingOrders = GlobalData::getInstance()->getPendingClientOrders();

        if (pendingOrders.empty()) {
            cout << "Нет заказов на отгрузку!" << endl;
            return;
        }

        viewPendingOrders();
        int choice;
        cout << "Выберите заказ для отгрузку: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > pendingOrders.size()) {
            throw runtime_error("Неверный выбор заказа!");
        }

        ClientOrder& order = pendingOrders[choice - 1];
        if (warehouse && warehouse->shipFromOrder(order)) {
            GlobalData::getInstance()->updateOrderStatus(order.getId());
            GlobalData::getInstance()->removePendingOrder(choice - 1);

            cout << "Заказ ID " << order.getId() << " успешно отгружен!" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при отгрузке заказа: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}