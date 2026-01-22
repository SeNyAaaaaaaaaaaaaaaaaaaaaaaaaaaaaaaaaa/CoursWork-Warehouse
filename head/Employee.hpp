#pragma once
#include "User.hpp"
#include "Date.hpp"
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Employee : public User {
protected:
    string position;
    double salary;
    Date hireDate;
    vector<string> schedule;

public:
    Employee(string uname = "", string pwd = "", string name = "",string pos = "", double sal = 0.0, Date hd = Date());

    virtual ~Employee() {}

    virtual void showMenu() = 0;

    void displayInfo() const;
    void setSalary(double sal);
    void setPosition(string pos);
    void addToSchedule(string day);
    double getSalary() const;
    string getPosition() const;
    vector<string> getSchedule() const;
};