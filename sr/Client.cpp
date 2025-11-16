#include "Client.hpp"
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

Client::Client(string name, string password) : UserSystem(name, password, "Client") {};

bool Client::login() {
    string username, password;
    cout << "=== ���� ������� ===" << endl;
    cout << "���: ";
    cin >> username;
    cout << "������: ";
    cin >> password;

    if (validateClient(username, password)) {
        this->name = username;
        this->password = password;
        cout << "�������� ����! ����� ����������, " << name << "!" << endl;
        return true;
    }

    cout << "�������� ������!" << endl;
    return false;
}

bool Client::validateClient(const string& username, const string& password) {
    auto clients = LoadUsersFromFile("Clients.txt");
    auto it = clients.find(username);
    return it != clients.end() && it->second == password;
}

void Client::showMenu() {
    int choice;
    do {
        cout << "\n=== ���� ������� ===" << endl;
        cout << "1. ������� �����" << endl;
        cout << "2. ������� �������" << endl;
        cout << "3. ���������� ����� �� ������.";
        cout << "4. �����" << endl;
        cout << "�������� ��������: ";
        cin >> choice;

        switch (choice) {
        case 1: makeOrder(); break;
        case 2: viewOrderHistory(); break;
            //case3/Warehouse
        case 4: cout << "�����..." << endl; break;
        default: cout << "�������� �����!" << endl;
        }
    } while (choice != 4);
}

void Client::makeOrder() {
    cout << "�������� ������..." << endl;
    orderHistory.push_back("����� #" + to_string(orderHistory.size() + 1));
    cout << "����� ������!" << endl;
}

void Client::viewOrderHistory() {
    cout << "=== ������� ������� ===" << endl;
    for (const auto& order : orderHistory) {
        cout << "- " << order << endl;
    }
}

Client* Client::registerClient() {
    string name, password;
    cout << "����������� �������" << endl;
    cout << "���: ";
    cin >> name;
    cout << "������: ";
    cin >> password;

    if (SaveUserIntoFile("Clients.txt", name, password, "Пользователь")) {
        cout << "����������� �������!" << endl;
        return new Client(name, password);
    }

    cout << "������ �����������!" << endl;
    return nullptr;
}

Client* Client::loginClient() {
    Client* client = new Client();
    if (client->login()) {
        return client;
    }
    delete client;
    return nullptr;
}