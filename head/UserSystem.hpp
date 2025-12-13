#include <string>
#include <map>
#include "Employee.hpp"
#include "Client.hpp"
using namespace std;

class UserSystem {
protected:
	string name;
	string role;
	string password;
public:
	UserSystem(string name = "", string password = "", string role = "");
	virtual ~UserSystem() = default;
	string getName() const;
	string getRole() const;
	string getPassword() const;
	virtual shared_ptr<Employee> loginEmployee();
	shared_ptr<Client> login();
	virtual bool logoutEmployee();
	bool logout();
	virtual void showMenu();
	static map<string, string> LoadUsersFromFile(const string& filename);
	static bool SaveUserIntoFile(const string& filename, const string& name, const string& password, const string& role);

};