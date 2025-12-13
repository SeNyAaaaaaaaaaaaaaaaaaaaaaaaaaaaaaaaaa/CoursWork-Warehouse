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
	void setProducts();
	void setQuantity();
	void setSuppliesId();
	static shared_ptr<Supply> findSupplyById(const int& Id);
    static shared_ptr<Supply> createSupply();
	void setDateDelevery(const string& Date);
    void setStatus(const string& Status);
};