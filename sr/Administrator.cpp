#include "Administrator.hpp"
#include "GlobalData.hpp"
#include <iostream>
#include <limits>
#include <memory>

Administrator::Administrator(string uname, string pwd, string name,string pos, double sal, Date hd): Employee(uname, pwd, name, pos, sal, hd) {}

void Administrator::showMenu() {
    int choice;
    do {
        try {
            cout << "\n================================" << endl;
            cout << "РЕЖИМ АДМИНИСТРАТОРА" << endl;
            cout << "Администратор: " << getFullName() << endl;
            cout << "================================" << endl;
            cout << "1. Добавить нового поставщика" << endl;
            cout << "2. Просмотреть всех поставщиков" << endl;
            cout << "3. Создать новую поставку" << endl;
            cout << "4. Просмотреть созданные поставки" << endl;
            cout << "5. Просмотреть товары поставщика" << endl;
            cout << "0. Выход" << endl;
            cout << "Выбор: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Неверный ввод. Введите число.");
            }

            switch (choice) {
            case 1: addSupplier(); break;
            case 2: viewSuppliers(); break;
            case 3: createSupply(); break;
            case 4: viewCreatedSupplies(); break;
            case 5: viewSupplierProducts(); break;
            case 0: cout << "Выход из режима администратора..." << endl; break;
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

void Administrator::addSupplier() {
    try {
        string name, contact, phone, email;

        cout << "\nДобавление нового поставщика:" << endl;
        cout << "Название компании: ";
        cin.ignore();
        getline(cin, name);
        cout << "Контактное лицо: ";
        getline(cin, contact);
        cout << "Телефон: ";
        getline(cin, phone);
        cout << "Email: ";
        getline(cin, email);

        Supplier newSupplier(name, contact, phone, email);

        char addMore;
        do {
            string pName, category, unit, specs;
            double price;

            cout << "\nДобавление товара поставщика:" << endl;
            cout << "Наименование товара: ";
            getline(cin, pName);
            cout << "Категория: ";
            getline(cin, category);
            cout << "Единица измерения: ";
            getline(cin, unit);
            cout << "Цена: ";
            cin >> price;
            if (cin.fail() || price < 0) {
                throw runtime_error("Некорректная цена!");
            }
            cin.ignore();
            cout << "Характеристики: ";
            getline(cin, specs);

            Product product(pName, category, unit, price, specs);
            newSupplier.addProduct(product);

            cout << "Добавить еще товар? (y/n): ";
            cin >> addMore;
            cin.ignore();
        } while (addMore == 'y' || addMore == 'Y');

        GlobalData::getInstance()->addSupplier(newSupplier);
        cout << "Поставщик добавлен успешно!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при добавлении поставщика: " << e.what() << endl;
    }
}

void Administrator::viewSuppliers() {
    try {
        vector<Supplier> suppliers = GlobalData::getInstance()->getSuppliers();

        if (suppliers.empty()) {
            cout << "Нет зарегистрированных поставщиков!" << endl;
            return;
        }

        cout << "\nСПИСОК ПОСТАВЩИКОВ:" << endl;
        for (int i = 0; i < suppliers.size(); i++) {
            cout << i + 1 << ". " << suppliers[i].getName() << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при получении списка поставщиков: " << e.what() << endl;
    }
}

void Administrator::createSupply() {
    try {
        vector<Supplier> suppliers = GlobalData::getInstance()->getSuppliers();

        if (suppliers.empty()) {
            cout << "Нет поставщиков для создания поставки!" << endl;
            return;
        }

        viewSuppliers();
        int supplierChoice;
        cout << "Выберите поставщика: ";
        cin >> supplierChoice;

        if (cin.fail() || supplierChoice < 1 || supplierChoice > suppliers.size()) {
            throw runtime_error("Неверный выбор поставщика!");
        }

        Supplier selectedSupplier = suppliers[supplierChoice - 1];

        int day, month, year;
        cout << "Введите дату доставки (день месяц год): ";
        cin >> day >> month >> year;

        if (cin.fail() || day < 1 || day > 31 || month < 1 || month > 12 || year < 2023) {
            throw runtime_error("Некорректная дата!");
        }

        Date deliveryDate(day, month, year);

        int nextId = 1;
        vector<Supply> allSupplies = GlobalData::getInstance()->getSupplies();
        if (!allSupplies.empty()) {
            for (const auto& supply : allSupplies) {
                if (supply.getId() >= nextId) {
                    nextId = supply.getId() + 1;
                }
            }
        }

        Supply newSupply(nextId, selectedSupplier, deliveryDate);
        newSupply.setAdministrator(getFullName());

        vector<Product> supplierProducts = selectedSupplier.getProducts();
        char addMore;
        do {
            cout << "\nДоступные товары поставщика:" << endl;
            for (int i = 0; i < supplierProducts.size(); i++) {
                cout << i + 1 << ". " << supplierProducts[i].getName()
                    << " - " << supplierProducts[i].getPrice()
                    << " руб./" << supplierProducts[i].getUnit() << endl;
            }

            int productChoice, quantity;
            cout << "Выберите товар: ";
            cin >> productChoice;
            cout << "Количество: ";
            cin >> quantity;

            if (productChoice >= 1 && productChoice <= supplierProducts.size() && quantity > 0) {
                newSupply.addProduct(supplierProducts[productChoice - 1], quantity);
            }
            else {
                throw runtime_error("Некорректный выбор товара или количества!");
            }

            cout << "Добавить еще товар? (y/n): ";
            cin >> addMore;
        } while (addMore == 'y' || addMore == 'Y');

        GlobalData::getInstance()->addSupply(newSupply);
        cout << "Поставка создана успешно! ID: " << newSupply.getId() << endl;
        cout << "Поставка передана менеджеру для приемки." << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при создании поставки: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Administrator::viewCreatedSupplies() {
    try {
        vector<Supply> supplies = GlobalData::getInstance()->getSupplies();

        if (supplies.empty()) {
            cout << "Нет созданных поставок!" << endl;
            return;
        }

        cout << "\nСОЗДАННЫЕ ПОСТАВКИ:" << endl;
        for (auto& supply : supplies) {
            supply.display();
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре поставок: " << e.what() << endl;
    }
}

void Administrator::viewSupplierProducts() {
    try {
        vector<Supplier> suppliers = GlobalData::getInstance()->getSuppliers();

        if (suppliers.empty()) {
            cout << "Нет поставщиков!" << endl;
            return;
        }

        viewSuppliers();
        int choice;
        cout << "Выберите поставщика для просмотра товаров: ";
        cin >> choice;

        if (choice >= 1 && choice <= suppliers.size()) {
            suppliers[choice - 1].display();
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре товаров поставщика: " << e.what() << endl;
    }
}