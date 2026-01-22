#include "Client.hpp"
#include <iostream>

Client::Client(string uname, string pwd, string name, string company, string addr, string ph): User(uname, pwd, "client", name), companyName(company), address(addr), phone(ph) {}

void Client::displayInfo() const {
    cout << "================================" << endl;
    cout << "Клиент: " << fullName << endl;
    cout << "Компания: " << companyName << endl;
    cout << "Адрес: " << address << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Логин: " << username << endl;
    cout << "================================" << endl;
}

void Client::addOrder(int orderId) {
    orderHistory.push_back(orderId);
}

string Client::getCompanyName() const { 
    return companyName;
}
string Client::getAddress() const {
    return address;
}
string Client::getPhone() const { 
    return phone; 
}
vector<int> Client::getOrderHistory() const {
    return orderHistory;
}