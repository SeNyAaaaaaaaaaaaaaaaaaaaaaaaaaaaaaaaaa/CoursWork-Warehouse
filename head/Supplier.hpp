#include <string>
#include <map>
#include <vector>
#include "Supply.hpp"
using namespace std;
class Supplier {
private:
    static int sup_id;
	static int next_sup_id;
	string name;
	string disc_of_prod_sup;
	string contact_info;
	static map<int, unique_ptr<Supplier>>Suppliers;
public:
	static void initSupplier();
	int getSupId() const;
	string getName() const;
	string getContact_Info() const;
    Supplier* findSupplier(int supplier_id) const;
    bool removeSupplier(int supplier_id);
    void displayAllSuppliers() const;
};