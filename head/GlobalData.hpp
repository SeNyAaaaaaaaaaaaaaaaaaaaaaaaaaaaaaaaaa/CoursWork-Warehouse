#pragma once
#include "Supplier.hpp"
#include "Supply.hpp"
#include "ClientOrder.hpp"
#include "Employee.hpp"
#include "Client.hpp"
#include <vector>
#include <memory>
using namespace std;


class Manager;
class StoreKeeper;
class Administrator;

class GlobalData {
private:
    static GlobalData* instance;
    vector<Supplier> suppliers;
    vector<Supply> supplies;
    vector<ClientOrder> clientOrders;
    vector<unique_ptr<Employee>> employees;
    vector<Client> clients;

    GlobalData() {}

public:
    GlobalData(const GlobalData&) = delete;
    GlobalData& operator=(const GlobalData&) = delete;

    static GlobalData* getInstance();

    void addSupplier(const Supplier& s);
    vector<Supplier> getSuppliers() const;
    Supplier* getSupplier(int index);
    int getSuppliersCount() const;

    void addSupply(const Supply& s);
    vector<Supply> getSupplies() const;
    Supply* findSupplyById(int id);
    vector<Supply> getPendingSupplies() const;
    vector<Supply> getAcceptedSupplies() const;
    void updateSupplyStatus(int supplyId);
    void removeSupply(int index);
    int getSuppliesCount() const;

    void addClientOrder(const ClientOrder& order);
    vector<ClientOrder> getClientOrders() const;
    vector<ClientOrder> getPendingClientOrders() const;
    vector<ClientOrder> getClientOrdersByUsername(const string& username) const;
    void updateOrderStatus(int orderId);
    void removePendingOrder(int index);
    int getClientOrdersCount() const;

    template<typename T>
    void addEmployee(unique_ptr<T> emp);

    vector<Employee*> getEmployees();
    Employee* getEmployeeByUsername(const string& username);
    bool removeEmployee(const string& username);
    void updateEmployeeSalary(const string& username, double newSalary);
    void addEmployeeSchedule(const string& username, const string& schedule);
    int getEmployeesCount() const;

    void addClient(const Client& client);
    vector<Client> getClients() const;
    Client* getClientByUsername(const string& username);
    int getClientsCount() const;

    void clearAllData();
};