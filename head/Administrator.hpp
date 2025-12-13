#include "Employee.hpp"
#include "Manager.hpp"
#include "StoreKeeper.hpp"
#include <memory>
#include <vector>
class Administrator: public Employee {
    public:
    static vector<shared_ptr<Manager>> AllManagers;
    static vector<shared_ptr<StoreKeeper>> AllStoreKeeper;
    private:
    void showMenu() override;
    shared_ptr<Employee> loginEmployee() override;
	bool logoutEmployee() override;
    
};