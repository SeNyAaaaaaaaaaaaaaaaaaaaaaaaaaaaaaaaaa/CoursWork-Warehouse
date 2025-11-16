#pragma once
#include "UserSystem.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <limits>

using namespace std;

UserSystem::UserSystem(string name, string role, string password) : name(name), role(role), password(password) {};

bool UserSystem::logout() {
    name = "";
    password = "";
    role = "";
    cout << "�� ������� ����� �� �������." << endl;
}

map<string, string> UserSystem::LoadUsersFromFile(const string& filename) {
    map<string, string> users;
    ifstream file(filename);
    string name, password;
    while (file >> name >> password) {
        users[name] = password;
    }
    file.close();
    return users;
}

bool UserSystem::SaveUserIntoFile(const string& filename, const string& name,
    const string& password, const string& role) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        return false;
    }

    if (role.empty()) {
        file << name << " " << password << endl;
    }
    else {
        file << name << " " << password << " " << role << endl;
    }
    file.close();
    return true;
}

string UserSystem::getName() const {
   return this->name;
}
string UserSystem::getPassword() const {
    return this->password;
}
string UserSystem::getRole() const {
    return this->role;
}