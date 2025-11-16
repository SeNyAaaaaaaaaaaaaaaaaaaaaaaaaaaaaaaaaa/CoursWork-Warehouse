#pragma once
#include "UserSystem.hpp"
#include <map>

class Employee : public UserSystem {
protected:
    int emp_id;
    int age;
    map<string, string> schedule;
    bool validateEmployee(const string& username, const string& password, const string& targetRole);
public:
    Employee(string name = "", string password = "", string role = "",int age = 0, int emp_id = 0);
    static Employee* loginEmployee(const string& targetRole);
    static map<string, tuple<string, string, int>> LoadEmployeeIntoFile();
};