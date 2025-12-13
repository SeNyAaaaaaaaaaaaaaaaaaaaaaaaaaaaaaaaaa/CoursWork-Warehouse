#include "Product.hpp"
#include "Order.hpp"
#include "Supply.hpp"
#include <string>
#include <map>
#include <iostream>
using namespace std;

Product::Product(int id, string type, string description, int quantity) : id(id), type(type), description(description), quantity(quantity) {}


void Product::createProduct() { 
    string type, description;
    int quantity;
    int id;
    getline(cin,type);
    getline(cin, description);
    id = next_id++;
    quantity = 0;
    products[id] =  make_shared<Product>(id, type, description,quantity);
}

shared_ptr<Product> Product::findProduct(int product_id) {
    auto it = products.find(product_id);
    if (it != products.end()) {
        return it->second;
    }
    return nullptr; 
}

     bool Product::removeProduct(int product_id) {
        return products.erase(product_id) > 0;
    }
    

 shared_ptr<Product> Product:: findProductByName(const string& name) {
        for (const auto& pair :  products) {
            if (pair.second->getName() == name) {
                return pair.second;
            }
        }
        return nullptr;
    }

void Product::displayAllProducts() {
    cout << "=== ВСЕ ПРОДУКТЫ ===" << endl;
    for (const auto& pair : products) {
        cout << "ID: " << pair.first << " | " << pair.second->getName()  << " | " << pair.second->getDescription() << endl;
    }
}

string Product::getDescription() const {
    return this->description;
}

void Product::decQuantity(shared_ptr<Addressing>, shared_ptr<Order>){

}
void Product::incQuantity(shared_ptr<Addressing>, shared_ptr<Supply>){

}