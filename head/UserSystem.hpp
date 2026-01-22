#pragma once
#include "User.hpp"
#include "Warehouse.hpp"
#include "Administrator.hpp"
#include "Manager.hpp"
#include "StoreKeeper.hpp"
#include "ClientRole.hpp"
#include <vector>
#include <memory>
using namespace std;

class UserSystem {
private:
    vector<unique_ptr<User>> users;
    shared_ptr<Warehouse> warehouse;

    void initializeUsers();
    void adminLogin();
    void managerLogin();
    void storekeeperLogin();
    void clientMenu();
    void clientLogin();
    void createClientAccount();

public:
    UserSystem();
    void run();
};