#include "Supplier.hpp"
#include "Supply.hpp"
#include <string>
#include <memory>
#include <Product.hpp>
#include <iostream>
using namespace std;

void Supplier::initSupplier() {
	string name_of_sup;
	cin >> name_of_sup;
	string type_of_product;
	cin >> type_of_product;
	string disc_of_prod;
	cin >> disc_of_prod;
	string contact_info;
	cin >> contact_info;
	sup_id = next_sup_id++;
	Suppliers[sup_id] = move(make_unique<Supplier>(sup_id, name_of_sup, type_of_product, disc_of_prod, contact_info));
}