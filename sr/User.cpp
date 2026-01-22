#include "User.hpp"

User::User(string uname, string pwd, string r, string name) : username(uname), password(pwd), role(r), fullName(name) {}

bool User::authenticate(string uname, string pwd) const {
    return username == uname && password == pwd;
}

string User::getUsername() const {
    return username;
}

string User::getRole() const {
    return role;
}

string User::getFullName() const {
    return fullName;
}

void User::setPassword(string pwd) {
    password = pwd;
}