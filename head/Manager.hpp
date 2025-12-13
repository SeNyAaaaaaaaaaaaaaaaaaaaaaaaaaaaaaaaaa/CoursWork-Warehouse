#include "Employee.hpp"
#include "StoreKeeper.hpp"
#include <memory>
#include <vector>
class Manager : public Employee {
    public:
    static vector<shared_ptr<StoreKeeper>> managedEmployees;
    private:
    void showMenu() override;
    shared_ptr<Employee>  loginEmployee() override;
	bool logoutEmployee() override;
    
};