#pragma once
#include "User.hpp"
#include <vector>
#include <string>
using namespace std;

class Client : public User {
private:
    string companyName;
    string address;
    string phone;
    vector<int> orderHistory;

public:
    Client(string uname = "", string pwd = "", string name = "", string company = "", string addr = "", string ph = "");
    void displayInfo() const;
    void addOrder(int orderId);
    string getCompanyName() const;
    string getAddress() const;
    string getPhone() const;
    vector<int> getOrderHistory() const;
};