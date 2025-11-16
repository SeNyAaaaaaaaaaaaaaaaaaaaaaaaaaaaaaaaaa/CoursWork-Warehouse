#include <string>
#include <map>
#include <memory>
using namespace std;
class Product {
private:
    static map<int, unique_ptr<Product>> products;
	static int next_id;
	int id;
	string type;
	string description;
	int quantity;
public:
    Product(int id, string type, string description, int quantity);

    static void createProduct();
    
    static Product* findProduct(int product_id);
    static void displayAllProducts();

    int getId() const;
    string getName() const;
	string getDescription() const;

	static bool removeProduct(int product_id);	
	static Product* findProductByName(const string& name);

};