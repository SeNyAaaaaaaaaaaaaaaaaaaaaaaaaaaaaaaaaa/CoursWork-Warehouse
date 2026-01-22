#pragma once
#include <string>
using namespace std;

class User {
protected:
    string username;
    string password;
    string role;
    string fullName;

public:
    User(string uname = "", string pwd = "", string r = "", string name = "");
    virtual ~User() {}
    bool authenticate(string uname, string pwd) const;
    string getUsername() const;
    string getRole() const;
    string getFullName() const;
    void setPassword(string pwd);
};