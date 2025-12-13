#include "Employee.hpp"
#include <fstream>
#include <map>
using namespace std;

Employee::Employee(string name, string password, string role, int age, int emp_id) : UserSystem(name, password, role), age(age), emp_id(emp_id) {};

bool Employee::validateEmployee(const string& username, const string& password,const string& targetRole) {
    auto employees = loadEmployeeDatabase();
    auto it = employees.find(username);
    if (it != employees.end()) {
        auto& [emp_password, emp_role, emp_age] = it->second;
        return emp_password == password && emp_role == targetRole;
    }
    return false;
}

map<string, tuple<string, string, int>> Employee::LoadEmployeeIntoFile() {
    map<string, tuple<string, string, int>> employees;
    ifstream file("employees.txt");
    string line;
    while (getline(file, line)) {
        string login, password, role, age_str;
		line = login + "|" + password + "|" + role + "|" + age_str;
        employees[login] = make_tuple(password, role, stoi(age_str));
    }
    file.close();
    return employees;
}

Employee* Employee::loginEmployee(const string& targetRole) {
    string username, password;
    cout << "=== ���� " << targetRole << " ===" << endl;
    cout << "�����: ";
    cin >> username;
    cout << "������: ";
    cin >> password;

    auto employees = loadEmployeeDatabase();
    auto it = employees.find(username);

    if (it != employees.end()) {
        auto& [emp_password, emp_role, emp_age] = it->second;
        if (emp_password == password && emp_role == targetRole) {
            if (targetRole == "�������������") {
                return new Administrator(username, password, emp_age, 0);
            }
            else if (targetRole == "��������") {
                return new Manager(username, password, emp_age, 0);
            }
            else if (targetRole == "���������") {
                return new Storekeeper(username, password, emp_age, 0);
            }
        }
    }
    cout << "�������� ������ ��� ������������ ����!" << endl;
    return nullptr;
}