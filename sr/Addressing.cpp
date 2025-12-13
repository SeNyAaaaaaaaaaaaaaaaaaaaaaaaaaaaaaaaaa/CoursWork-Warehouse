#include "Addressing.hpp"
#include <iostream>
using namespace std;

shared_ptr<Addressing> Addressing::makeAdress() const {
    string storage_a;
    cin >> storage_a;
    string ro;
    cin >> ro;
    string cel;
    cin >> cel;
    adress_index = next_adress_index++;
    addres[adress_index] = make_shared<Addressing>(storage_a, ro, cel);
}
string Addressing::getCell() const {
    return this->cell;
}
string Addressing::getRow() const {
    return this->row;
}
string Addressing::getStorage_Area() const {
    return this->storage_area;
}
int Addressing::getIndex() const {
    return this->adress_index;
}
shared_ptr<Addressing> Addressing::getAddressing(const int& adress_index) const {
    return addres[adress_index];
}
