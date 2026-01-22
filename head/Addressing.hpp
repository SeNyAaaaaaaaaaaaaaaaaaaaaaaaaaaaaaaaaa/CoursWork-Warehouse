#pragma once
#include <string>
using namespace std;

class Addressing {
private:
    string zone;
    int rack;
    int shelf;
    int cell;

public:
    Addressing(string z = "A", int r = 1, int s = 1, int c = 1);
    string getFullAddress() const;
    void display() const;
    string getZone() const;
    int getRack() const;
    int getShelf() const;
    int getCell() const;
};