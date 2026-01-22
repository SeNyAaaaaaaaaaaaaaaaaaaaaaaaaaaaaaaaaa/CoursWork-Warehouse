#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
using namespace std;

class Date {
private:
    int day, month, year;

public:
    Date(int d = 1, int m = 1, int y = 2024);
    static Date getCurrentDate();
    bool operator==(const Date& other) const;
    void display() const;
    string toString() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
};