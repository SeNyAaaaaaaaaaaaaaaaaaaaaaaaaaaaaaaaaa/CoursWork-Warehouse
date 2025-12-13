#include "Employee.hpp"
#include "UserSystem.hpp"
#include <memory>
#include <vector>
class StoreKeeper: public Employee {
    public:
    private:
    void showMenu() override;
    shared_ptr<Employee> loginEmployee() override;
	bool logoutEmployee() override;
    
};