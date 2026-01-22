#include "Addressing.hpp"
#include <iostream>

Addressing::Addressing(string z, int r, int s, int c): zone(z), rack(r), shelf(s), cell(c) {}

string Addressing::getFullAddress() const {
    return zone + "-" + to_string(rack) + "-" + to_string(shelf) + "-" + to_string(cell);
}

void Addressing::display() const {
    cout << "Адрес хранения: " << getFullAddress() << endl;
}

string Addressing::getZone() const { 
    return zone;
}
int Addressing::getRack() const {
    return rack; 
}
int Addressing::getShelf() const {
    return shelf;
}
int Addressing::getCell() const { 
    return cell; 
}