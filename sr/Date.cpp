#include "Date.hpp"

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date Date::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return Date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

void Date::display() const {
    cout << setw(2) << setfill('0') << day << "." << setw(2) << setfill('0') << month << "." << year;
}

string Date::toString() const {
    stringstream ss;
    ss << setw(2) << setfill('0') << day << "." << setw(2) << setfill('0') << month << "." << year;
    return ss.str();
}

int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}