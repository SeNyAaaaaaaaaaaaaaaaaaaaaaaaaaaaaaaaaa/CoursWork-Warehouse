#include "Product.hpp"
#include "Addressing.hpp"
class Warehouse {
    private:
    using WrhMaper = map<shared_ptr<Addressing>, map<shared_ptr<Product>, int>>;
    WrhMaper wrh;
    int capacity;

    public:
    Warehouse() {};
    Warehouse(int capacity): capacity(capacity) {};
    void showAllProductWh() const;
    void addProductOnWh(shared_ptr<Product> prod);
    void processSupply();
    void processOrder();
    int getCapacity() const;
    bool checkCapacity() const;
    void eraseProductOfWh();
};