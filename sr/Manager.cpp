#include "Manager.hpp"
#include "GlobalData.hpp"
#include "Administrator.hpp"
#include "StoreKeeper.hpp"
#include <iostream>
#include <limits>
#include <memory>

using namespace std;

Manager::Manager(string uname, string pwd, string name,string pos, double sal, Date hd,shared_ptr<Warehouse> w): Employee(uname, pwd, name, pos, sal, hd), warehouse(w) {}

void Manager::showMenu() {
    int choice;
    do {
        try {
            cout << "\n================================" << endl;
            cout << "РЕЖИМ МЕНЕДЖЕРА" << endl;
            cout << "Менеджер: " << getFullName() << endl;
            cout << "================================" << endl;
            cout << "1. Принять поставку на склад" << endl;
            cout << "2. Просмотреть ожидающие поставки" << endl;
            cout << "3. Нанять нового сотрудника" << endl;
            cout << "4. Уволить сотрудника" << endl;
            cout << "5. Просмотреть всех сотрудников" << endl;
            cout << "6. Назначить зарплату сотруднику" << endl;
            cout << "7. Добавить в расписание сотрудника" << endl;
            cout << "8. Просмотреть расписание сотрудника" << endl;
            cout << "9. Просмотреть текущий инвентарь" << endl;
            cout << "0. Выход" << endl;
            cout << "Выбор: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Неверный ввод. Введите число.");
            }

            switch (choice) {
            case 1: acceptSupply(); break;
            case 2: viewPendingSupplies(); break;
            case 3: hireEmployee(); break;
            case 4: fireEmployee(); break;
            case 5: viewEmployees(); break;
            case 6: setEmployeeSalary(); break;
            case 7: addToSchedule(); break;
            case 8: viewEmployeeSchedule(); break;
            case 9: if (warehouse) warehouse->displayInventory(); break;
            case 0: cout << "Выход из режима менеджера..." << endl; break;
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

void Manager::acceptSupply() {
    try {
        vector<Supply> pendingSupplies = GlobalData::getInstance()->getPendingSupplies();

        if (pendingSupplies.empty()) {
            cout << "Нет поставок для приемки!" << endl;
            return;
        }

        cout << "\nОЖИДАЮЩИЕ ПРИЕМКИ ПОСТАВКИ:" << endl;
        for (int i = 0; i < pendingSupplies.size(); i++) {
            cout << i + 1 << ". ";
            pendingSupplies[i].display();
        }

        int choice;
        cout << "Выберите поставку для приемки: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > pendingSupplies.size()) {
            throw runtime_error("Неверный выбор поставки!");
        }

        int selectedSupplyId = pendingSupplies[choice - 1].getId();

        cout << "\n=== ПРИЕМКА ПОСТАВКИ ID " << selectedSupplyId << " ===" << endl;

        Supply* originalSupply = GlobalData::getInstance()->findSupplyById(selectedSupplyId);

        if (originalSupply) {
            if (!originalSupply->getIsAccepted()) {
                originalSupply->acceptSupply();
                cout << "Статус поставки изменен на ПРИНЯТА" << endl;

                if (warehouse) {
                    warehouse->addFromSupply(*originalSupply);
                }

                cout << "Поставка ID " << originalSupply->getId() << " принята успешно!" << endl;
            }
            else {
                cout << "Поставка уже принята!" << endl;
            }
        }
        else {
            cout << "Поставка не найдена в GlobalData!" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при приемке поставки: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Manager::viewPendingSupplies() {
    try {
        vector<Supply> pendingSupplies = GlobalData::getInstance()->getPendingSupplies();

        if (pendingSupplies.empty()) {
            cout << "Нет ожидающих поставок!" << endl;
            return;
        }

        cout << "\nОЖИДАЮЩИЕ ПРИЕМКИ ПОСТАВКИ:" << endl;
        for (int i = 0; i < pendingSupplies.size(); i++) {
            pendingSupplies[i].display();
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре поставок: " << e.what() << endl;
    }
}

void Manager::hireEmployee() {
    try {
        string username, password, fullName, position;
        double salary;

        cout << "\nНаем нового сотрудника:" << endl;
        cout << "ФИО: ";
        cin.ignore();
        getline(cin, fullName);
        cout << "Должность: ";
        getline(cin, position);
        cout << "Логин: ";
        getline(cin, username);
        cout << "Пароль: ";
        getline(cin, password);
        cout << "Зарплата: ";
        cin >> salary;

        if (cin.fail() || salary < 0) {
            throw runtime_error("Некорректная зарплата!");
        }

        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();
        for (const auto& emp : employees) {
            if (emp->getUsername() == username) {
                throw runtime_error("Пользователь с таким логином уже существует!");
            }
        }

        if (position == "Manager") {
            auto newEmployee = make_unique<Manager>(username, password, fullName, position, salary, Date::getCurrentDate(), warehouse);
            GlobalData::getInstance()->addEmployee<Manager>(move(newEmployee));
        }
        else if (position == "StoreKeeper") {
            auto newEmployee = make_unique<StoreKeeper>(username, password, fullName, position, salary, Date::getCurrentDate(), warehouse);
            GlobalData::getInstance()->addEmployee<StoreKeeper>(move(newEmployee));
        }
        else if (position == "Admin") {
            auto newEmployee = make_unique<Administrator>(username, password, fullName, position, salary, Date::getCurrentDate());
            GlobalData::getInstance()->addEmployee<Administrator>(move(newEmployee));
        }
        else {
            throw runtime_error("Неизвестная должность! Используйте: Менеджер, Кладовщик или Администратор");
        }

        cout << "Сотрудник нанят успешно!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при найме сотрудника: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Manager::fireEmployee() {
    try {
        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();

        if (employees.empty()) {
            cout << "Нет сотрудников!" << endl;
            return;
        }

        viewEmployees();
        int choice;
        cout << "Выберите сотрудника для увольнения: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > employees.size()) {
            throw runtime_error("Неверный выбор сотрудника!");
        }

        string username = employees[choice - 1]->getUsername();

        if (username == getUsername()) {
            throw runtime_error("Нельзя уволить самого себя!");
        }

        if (GlobalData::getInstance()->removeEmployee(username)) {
            cout << "Сотрудник " << employees[choice - 1]->getFullName() << " уволен!" << endl;
        }
        else {
            cout << "Ошибка при увольнении сотрудника!" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при увольнении сотрудника: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Manager::viewEmployees() {
    try {
        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();

        if (employees.empty()) {
            cout << "Нет сотрудников!" << endl;
            return;
        }

        cout << "\nСОТРУДНИКИ:" << endl;
        for (int i = 0; i < employees.size(); i++) {
            cout << i + 1 << ". ";
            employees[i]->displayInfo();
            cout << "------------------------" << endl;
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре сотрудников: " << e.what() << endl;
    }
}

void Manager::setEmployeeSalary() {
    try {
        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();

        if (employees.empty()) {
            cout << "Нет сотрудников!" << endl;
            return;
        }

        viewEmployees();
        int choice;
        double newSalary;

        cout << "Выберите сотрудника: ";
        cin >> choice;
        cout << "Новая зарплата: ";
        cin >> newSalary;

        if (cin.fail() || choice < 1 || choice > employees.size() || newSalary < 0) {
            throw runtime_error("Некорректные данные!");
        }

        string username = employees[choice - 1]->getUsername();

        GlobalData::getInstance()->updateEmployeeSalary(username, newSalary);
        cout << "Зарплата обновлена!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при изменении зарплаты: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Manager::addToSchedule() {
    try {
        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();

        if (employees.empty()) {
            cout << "Нет сотрудников!" << endl;
            return;
        }

        viewEmployees();
        int choice;
        string day;

        cout << "Выберите сотрудника: ";
        cin >> choice;
        cin.ignore();
        cout << "День работы (например: Понедельник 9:00-18:00): ";
        getline(cin, day);

        if (choice < 1 || choice > employees.size()) {
            throw runtime_error("Неверный выбор сотрудника!");
        }

        string username = employees[choice - 1]->getUsername();

        GlobalData::getInstance()->addEmployeeSchedule(username, day);
        cout << "Расписание обновлено!" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при добавлении в расписание: " << e.what() << endl;
    }
}

void Manager::viewEmployeeSchedule() {
    try {
        vector<Employee*> employees = GlobalData::getInstance()->getEmployees();

        if (employees.empty()) {
            cout << "Нет сотрудников!" << endl;
            return;
        }

        viewEmployees();
        int choice;

        cout << "Выберите сотрудника для просмотра расписания: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > employees.size()) {
            throw runtime_error("Неверный выбор сотрудника!");
        }

        vector<string> schedule = employees[choice - 1]->getSchedule();
        if (schedule.empty()) {
            cout << "У сотрудника нет установленного расписания." << endl;
        }
        else {
            cout << "\nРасписание сотрудника " << employees[choice - 1]->getFullName() << ":" << endl;
            for (int i = 0; i < schedule.size(); i++) {
                cout << i + 1 << ". " << schedule[i] << endl;
            }
        }
    }
    catch (const exception& e) {
        cout << "Ошибка при просмотре расписания: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}