#include "Product.hpp"
#include <iostream>

Product::Product(string n, string cat, string u, double p, string spec) : name(n), category(cat), unit(u), price(p), specifications(spec) {}

void Product::display() const {
    cout << "Наименование: " << name << endl;
    cout << "Категория: " << category << endl;
    cout << "Ед. измерения: " << unit << endl;
    cout << "Цена: " << price << " руб." << endl;
    cout << "Характеристики: " << specifications << endl;
}

string Product::getName() const {
    return name;
}

string Product::getCategory() const {
    return category;
}

string Product::getUnit() const {
    return unit;
}

double Product::getPrice() const {
    return price;
}

string Product::getSpecifications() const {
    return specifications;
}

void Product::setPrice(double p) {
    price = p;
}