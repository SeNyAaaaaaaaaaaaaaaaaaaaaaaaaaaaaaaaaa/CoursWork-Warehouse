#include "Order.hpp"
#include <memory>
using namespace std;
void Order::createOrder() {
    orders[OrderID] =  make_shared<Order>(productsIdAndQuantity);
}
int Order::getOrderID() {
    return this->OrderID;
}