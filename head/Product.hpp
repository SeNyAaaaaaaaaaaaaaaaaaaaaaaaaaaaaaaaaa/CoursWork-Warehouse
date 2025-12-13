#pragma once
#include <string>
#include <map>
#include <memory>
#include "Addressing.hpp"
#include "Order.hpp"
using namespace std;
class Product {
private:
    static map<int, shared_ptr<Product>> products;
	static int next_id;
	int id;
	string type;
	string description;
	int quantity;
public:
    Product(int id, string type, string description, int quantity);

    static void createProduct();
    static shared_ptr<Product> findProduct(int product_id);
    static void displayAllProducts();

    int getId() const;
    string getName() const;
	string getDescription() const;
	static bool removeProduct(int product_id);	
	static shared_ptr<Product> findProductByName(const string& name);
	void decQuantity(shared_ptr<Addressing>, shared_ptr<Order>);
    void incQuantity(shared_ptr<Addressing>, shared_ptr<Supply>);

};