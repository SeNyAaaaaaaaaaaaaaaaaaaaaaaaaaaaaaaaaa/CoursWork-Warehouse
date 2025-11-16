#include <string>
#include <map>
#include <vector>
#include "Supply.hpp"
using namespace std;
class Supplier {
private:
	int sup_id;
	string name;
	string disc_of_prod_sup;
	string contact_info;
	map<int, unique_ptr<Supplier>>Suppliers;
public:
	Supplier* initSupplier();
	int getSupId() const;
	string getName() const;
	string getContact_Info() const;
	Supply* createSupply();
};