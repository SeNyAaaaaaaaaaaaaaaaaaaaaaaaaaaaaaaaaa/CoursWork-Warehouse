#include "UserSystem.hpp"
#include "GlobalData.hpp"
#include "Administrator.hpp"
#include "Manager.hpp"
#include "StoreKeeper.hpp"
#include <iostream>
#include <limits>
#include <memory>

using namespace std;

UserSystem::UserSystem() : warehouse(make_shared<Warehouse>()) {initializeUsers();}

void UserSystem::initializeUsers() {
    users.push_back(make_unique<Administrator>("Admin", "admin123", "Иванов Иван Иванович"));
    users.push_back(make_unique<Manager>("Manager", "manager123", "Петров Петр Петрович", "Manager", 50000.0, Date(), warehouse));
    users.push_back(make_unique<StoreKeeper>("StoreKeeper", "keeper123", "Сидоров Сидор Сидорович", "StoreKeeper", 35000.0, Date(), warehouse));
}

void UserSystem::run() {
    while (true) {
        try {
            cout << "\n================================" << endl;
            cout << "СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ СТРОЙМАТЕРИАЛОВ" << endl;
            cout << "================================" << endl;
            cout << "Выберите режим работы:" << endl;
            cout << "1. Администратор склада" << endl;
            cout << "2. Менеджер склада" << endl;
            cout << "3. Кладовщик" << endl;
            cout << "4. Клиент склада" << endl;
            cout << "5. Выход из программы" << endl;
            cout << "Выбор: ";

            int choice;
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Неверный ввод. Введите число.");
            }

            switch (choice) {
            case 1: adminLogin(); break;
            case 2: managerLogin(); break;
            case 3: storekeeperLogin(); break;
            case 4: clientMenu(); break;
            case 5:
                cout << "Выход из программы..." << endl;
                return;
            default:
                cout << "Неверный выбор!" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }
        catch (...) {
            cout << "Неизвестная ошибка!" << endl;
        }
    }
}

void UserSystem::managerLogin() {
    try {
        string username, password;
        cout << "\n=== ВХОД МЕНЕДЖЕРА ===" << endl;
        cout << "Логин: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        for (auto& user : users) {
            Manager* manager = dynamic_cast<Manager*>(user.get());
            if (manager && manager->authenticate(username, password)) {
                manager->showMenu();
                return;
            }
        }

        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();
        for (auto& emp : employees) {
            if (emp->getPosition() == "Manager" && emp->authenticate(username, password)) {
                Manager* manager = dynamic_cast<Manager*>(emp);
                if (manager) {
                    manager->showMenu();
                    return;
                }
            }
        }

        cout << "Неверный логин или пароль!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при входе менеджера: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void UserSystem::storekeeperLogin() {
    try {
        string username, password;
        cout << "\n=== ВХОД КЛАДОВЩИКА ===" << endl;
        cout << "Логин: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        for (auto& user : users) {
            StoreKeeper* keeper = dynamic_cast<StoreKeeper*>(user.get());
            if (keeper && keeper->authenticate(username, password)) {
                keeper->showMenu();
                return;
            }
        }

        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();
        for (auto& emp : employees) {
            if (emp->getPosition() == "StoreKeeper" && emp->authenticate(username, password)) {
                StoreKeeper* keeper = dynamic_cast<StoreKeeper*>(emp);
                if (keeper) {
                    keeper->showMenu();
                    return;
                }
            }
        }

        cout << "Неверный логин или пароль!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при входе кладовщика: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void UserSystem::adminLogin() {
    try {
        string username, password;
        cout << "\n=== ВХОД АДМИНИСТРАТОРА ===" << endl;
        cout << "Логин: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        for (auto& user : users) {
            Administrator* admin = dynamic_cast<Administrator*>(user.get());
            if (admin && admin->authenticate(username, password)) {
                admin->showMenu();
                return;
            }
        }

        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();
        for (auto& emp : employees) {
            if (emp->getPosition() == "Admin" && emp->authenticate(username, password)) {
                Administrator* admin = dynamic_cast<Administrator*>(emp);
                if (admin) {
                    admin->showMenu();
                    return;
                }
            }
        }

        cout << "Неверный логин или пароль!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при входе администратора: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void UserSystem::clientMenu() {
    try {
        cout << "\n=== РЕЖИМ КЛИЕНТА ===" << endl;
        cout << "1. Войти в существующий аккаунт" << endl;
        cout << "2. Создать новый аккаунт" << endl;
        cout << "Выбор: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Неверный ввод. Введите число.");
        }

        if (choice == 1) {
            clientLogin();
        }
        else if (choice == 2) {
            createClientAccount();
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    catch (...) {
        cout << "Неизвестная ошибка!" << endl;
    }
}

void UserSystem::clientLogin() {
    try {
        string username, password;
        cout << "\n=== ВХОД КЛИЕНТА ===" << endl;
        cout << "Логин: ";
        cin >> username;
        cout << "Пароль: ";
        cin >> password;

        vector<Client> clients = GlobalData::getInstance()->getClients();
        for (auto& client : clients) {
            if (client.authenticate(username, password)) {
                ClientRole clientRole(client, warehouse);
                clientRole.showMenu();
                return;
            }
        }

        cout << "Неверный логин или пароль!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при входе клиента: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void UserSystem::createClientAccount() {
    try {
        string username, password, fullName, company, address, phone;

        cout << "\n=== СОЗДАНИЕ АККАУНТА КЛИЕНТА ===" << endl;
        cout << "ФИО: ";
        cin.ignore();
        getline(cin, fullName);
        cout << "Название компании: ";
        getline(cin, company);
        cout << "Адрес: ";
        getline(cin, address);
        cout << "Телефон: ";
        getline(cin, phone);
        cout << "Логин: ";
        getline(cin, username);
        cout << "Пароль: ";
        getline(cin, password);

        vector<Client> clients = GlobalData::getInstance()->getClients();
        for (auto& client : clients) {
            if (client.getUsername() == username) {
                throw runtime_error("Пользователь с таким логином уже существует!");
            }
        }

        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();
        for (auto& emp : employees) {
            if (emp->getUsername() == username) {
                throw runtime_error("Пользователь с таким логином уже существует!");
            }
        }

        for (auto& user : users) {
            if (user->getUsername() == username) {
                throw runtime_error("Пользователь с таким логином уже существует!");
            }
        }

        if (username.empty() || password.empty() || fullName.empty()) {
            throw runtime_error("Логин, пароль и ФИО не могут быть пустыми!");
        }

        Client newClient(username, password, fullName, company, address, phone);
        GlobalData::getInstance()->addClient(newClient);

        cout << "Аккаунт создан успешно! Теперь вы можете войти." << endl;
        clientLogin();
    }
    catch (const exception& e) {
        cout << "Ошибка при создании аккаунта: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    catch (...) {
        cout << "Неизвестная ошибка при создании аккаунта!" << endl;
    }
}