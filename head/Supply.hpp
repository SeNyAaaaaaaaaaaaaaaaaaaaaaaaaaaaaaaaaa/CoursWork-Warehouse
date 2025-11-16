#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;
class Supply {
private:
	int supplies_id;
	string date_of_delivery;
	string statatus;
	string products;
	int quantity;
	vector<unique_ptr<Supply>>supplies;
public:
	void setIdsupply();
	void setStatus();
	void setProducts();
	void setStatus();
	void setQuantity();
	void setSuppliesId();
};