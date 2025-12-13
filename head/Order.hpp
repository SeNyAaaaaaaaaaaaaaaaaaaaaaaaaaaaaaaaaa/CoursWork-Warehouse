#include <vector>
#include<map>
#include <string>
using namespace std;
class Order {

private:
static int OrderID;
vector<pair<int, int>> productsIdAndQuantity;
static map<int, shared_ptr<Order>> orders;
string status;
string shipment_date;

public:
Order(vector<pair<int, int>> productsIdAndQuantity, string shipment_date, string status="Не отгруженно", static int OrderID);
void createOrder();
shared_ptr<Order> getOrder();
int getOrderID();

};