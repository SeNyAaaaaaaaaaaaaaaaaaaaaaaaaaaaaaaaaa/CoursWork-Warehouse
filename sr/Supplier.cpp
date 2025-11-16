#include "Supplier.hpp"
#include "Supply.hpp"
#include <string>
#include <memory>
#include <Product.hpp>
#include <iostream>
using namespace std;

Supplier* Supplier::initSupplier() {
	string name_of_sup;
	cin >> name_of_sup;
	string type_of_product;
	cin >> type_of_product;
	string disc_of_prod;
	cin >> disc_of_prod;
	string contact_info;
	cin >> contact_info;
	this->name = name_of_sup;
	this->contact_info = contact_info;
	Product prod;
	prod.initProduct(type_of_product,disc_of_prod);
	Suppliers.insert(make_pair(sup_id, make_unique<Supplier>()));
	return this;
}
Supply* Supplier::createSupply() {

}