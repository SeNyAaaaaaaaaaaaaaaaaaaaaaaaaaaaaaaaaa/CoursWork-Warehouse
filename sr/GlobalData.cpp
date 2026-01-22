#include "GlobalData.hpp"
#include "Administrator.hpp"
#include "Manager.hpp"
#include "StoreKeeper.hpp"
#include <iostream>

GlobalData* GlobalData::instance = nullptr;

GlobalData* GlobalData::getInstance() {
    if (!instance) {
        instance = new GlobalData();
    }
    return instance;
}

void GlobalData::addSupplier(const Supplier& s) {
    suppliers.push_back(s);
}

vector<Supplier> GlobalData::getSuppliers() const {
    return suppliers;
}

Supply* GlobalData::findSupplyById(int id) {
    for (auto& supply : supplies) {
        if (supply.getId() == id) {
            return &supply;
        }
    }
    return nullptr;
}

Supplier* GlobalData::getSupplier(int index) {
    if (index >= 0 && index < suppliers.size()) {
        return &suppliers[index];
    }
    return nullptr;
}

int GlobalData::getSuppliersCount() const {
    return suppliers.size();
}

void GlobalData::addSupply(const Supply& s) {
    supplies.push_back(s);
}

vector<Supply> GlobalData::getSupplies() const {
    return supplies;
}

vector<Supply> GlobalData::getPendingSupplies() const {
    vector<Supply> pending;
    for (const auto& supply : supplies) {
        if (!supply.getIsAccepted()) {
            pending.push_back(supply);
        }
    }
    return pending;
}

vector<Supply> GlobalData::getAcceptedSupplies() const {
    vector<Supply> accepted;
    for (const auto& supply : supplies) {
        if (supply.getIsAccepted()) {
            accepted.push_back(supply);
        }
    }
    return accepted;
}

void GlobalData::updateSupplyStatus(int supplyId) {
    for (auto& supply : supplies) {
        if (supply.getId() == supplyId) {
            cout << "Статус изменен для поставки " << supplyId << " на принято" << endl;
            supply.acceptSupply();
            return;
        }
    }
    cout << "Поставка " << supplyId << " не найдена!" << endl;
}

void GlobalData::removeSupply(int index) {
    if (index >= 0 && index < supplies.size()) {
        supplies.erase(supplies.begin() + index);
    }
}

int GlobalData::getSuppliesCount() const {
    return supplies.size();
}

void GlobalData::addClientOrder(const ClientOrder& order) {
    clientOrders.push_back(order);
}

vector<ClientOrder> GlobalData::getClientOrders() const {
    return clientOrders;
}

vector<ClientOrder> GlobalData::getPendingClientOrders() const {
    vector<ClientOrder> pending;
    for (const auto& order : clientOrders) {
        if (!order.getIsShipped()) {
            pending.push_back(order);
        }
    }
    return pending;
}

vector<ClientOrder> GlobalData::getClientOrdersByUsername(const string& username) const {
    vector<ClientOrder> result;
    for (const auto& order : clientOrders) {
        if (order.getClient().getUsername() == username) {
            result.push_back(order);
        }
    }
    return result;
}

void GlobalData::updateOrderStatus(int orderId) {
    for (auto& order : clientOrders) {
        if (order.getId() == orderId) {
            order.shipOrder();
            break;
        }
    }
}

void GlobalData::removePendingOrder(int index) {
    vector<ClientOrder> pending = getPendingClientOrders();
    if (index >= 0 && index < pending.size()) {
        int orderId = pending[index].getId();
        for (auto it = clientOrders.begin(); it != clientOrders.end(); ++it) {
            if (it->getId() == orderId) {
                clientOrders.erase(it);
                break;
            }
        }
    }
}

int GlobalData::getClientOrdersCount() const {
    return clientOrders.size();
}


template<typename T>
void GlobalData::addEmployee(unique_ptr<T> emp) {
    employees.push_back(move(emp));
}

template void GlobalData::addEmployee<Employee>(unique_ptr<Employee> emp);
template void GlobalData::addEmployee<Manager>(unique_ptr<Manager> emp);
template void GlobalData::addEmployee<StoreKeeper>(unique_ptr<StoreKeeper> emp);
template void GlobalData::addEmployee<Administrator>(unique_ptr<Administrator> emp);

vector<Employee*> GlobalData::getEmployees() {
    vector<Employee*> result;
    for (auto& emp : employees) {
        result.push_back(emp.get());
    }
    return result;
}

Employee* GlobalData::getEmployeeByUsername(const string& username) {
    for (auto& emp : employees) {
        if (emp->getUsername() == username) {
            return emp.get();
        }
    }
    return nullptr;
}

bool GlobalData::removeEmployee(const string& username) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getUsername() == username) {
            employees.erase(it);
            return true;
        }
    }
    return false;
}

void GlobalData::updateEmployeeSalary(const string& username, double newSalary) {
    for (auto& emp : employees) {
        if (emp->getUsername() == username) {
            emp->setSalary(newSalary);
            break;
        }
    }
}

void GlobalData::addEmployeeSchedule(const string& username, const string& schedule) {
    for (auto& emp : employees) {
        if (emp->getUsername() == username) {
            emp->addToSchedule(schedule);
            break;
        }
    }
}

int GlobalData::getEmployeesCount() const {
    return employees.size();
}

void GlobalData::addClient(const Client& client) {
    clients.push_back(client);
}

vector<Client> GlobalData::getClients() const {
    return clients;
}

Client* GlobalData::getClientByUsername(const string& username) {
    for (auto& client : clients) {
        if (client.getUsername() == username) {
            return &client;
        }
    }
    return nullptr;
}

int GlobalData::getClientsCount() const {
    return clients.size();
}

void GlobalData::clearAllData() {
    suppliers.clear();
    supplies.clear();
    clientOrders.clear();
    employees.clear();
    clients.clear();
}