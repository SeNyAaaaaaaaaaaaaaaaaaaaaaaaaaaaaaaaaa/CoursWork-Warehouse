#pragma once
#include "UserSystem.hpp"
#include <string>
#include <vector>

class Client : public UserSystem {
private:
    string name;
    string password;
    vector<string> orderHistory;
    bool validateClient(const string& username, const string& password);
public:
    Client(string name = "", string password = "");
    bool login() override;
    void showMenu() override;
    void makeOrder();
    void viewOrderHistory();
    static Client* registerClient();
    static Client* loginClient();
};