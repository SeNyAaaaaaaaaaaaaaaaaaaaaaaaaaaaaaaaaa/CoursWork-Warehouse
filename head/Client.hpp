#pragma once
#include "Order.hpp"
#include "UserSystem.hpp"
#include <string>
#include <vector>

class Client : public UserSystem {
protected:
    string name;
    string password;
    static vector<string> orderHistory;
    private:
    bool validateClient(const string& username, const string& password);
public:
    Client(string name = "", string password = "");
    bool login();
    void showMenu() override;
    void viewOrderHistory();
    static Client* registerClient();
    static Client* loginClient();
};