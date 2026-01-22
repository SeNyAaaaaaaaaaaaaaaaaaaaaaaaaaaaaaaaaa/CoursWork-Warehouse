#include "Employee.hpp"
#include <iostream>

Employee::Employee(string uname, string pwd, string name,string pos, double sal, Date hd): User(uname, pwd, "employee", name), position(pos), salary(sal), hireDate(hd) {}

void Employee::displayInfo() const {
    cout << "ФИО: " << fullName << endl;
    cout << "Должность: " << position << endl;
    cout << "Зарплата: " << salary << " руб." << endl;
    cout << "Дата найма: "; hireDate.display(); cout << endl;
    cout << "Логин: " << username << endl;
}

void Employee::setSalary(double sal) {
    salary = sal;
}

void Employee::setPosition(string pos) {
    position = pos;
}

void Employee::addToSchedule(string day) {
    schedule.push_back(day);
}

double Employee::getSalary() const {
    return salary;
}

string Employee::getPosition() const {
    return position;
}

vector<string> Employee::getSchedule() const {
    return schedule;
}