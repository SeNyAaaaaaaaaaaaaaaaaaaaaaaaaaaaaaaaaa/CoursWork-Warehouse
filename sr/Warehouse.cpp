#include "Warehouse.hpp"
#include <iostream>
using namespace std;

void Warehouse::showAllProductWh() const {
    cout << "|ВСЕ ДОСТУПНЫЕ ТОВАРЫ|";
    for(const auto& iter: wrh) {
        auto first_prod = iter.second.begin();
        cout << "Продукт: " << first_prod->first->getName() << "|" << "Количество: " << to_string(first_prod->second) << endl;
    }
}

void Warehouse::addProductOnWh(shared_ptr<Product> prod) {
    for(const auto& iter : wrh) {
        auto product = iter.second.begin();
        if(prod->getId() == product->first->getId()) {
            cout << "Продукт - " + product->first->getName() << "уже сущетсвует в базе склада.";
        }else{wrh[iter.first->makeAdress()][prod->findProduct(prod->getId())] = 0;}
    }
}

