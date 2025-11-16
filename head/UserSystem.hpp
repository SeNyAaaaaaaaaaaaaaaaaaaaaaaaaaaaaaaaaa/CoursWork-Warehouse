#include <string>
#include <map>
using namespace std;

class UserSystem {
private:
	string name;
	string role;
	string password;
public:
	UserSystem(string name = "", string password = "", string role = "");
	virtual ~UserSystem() = default;
	string getName() const;
	string getRole() const;
	string getPassword() const;
	virtual bool login();
	virtual bool logout();
	virtual void showMenu();
	static map<string, string> LoadUsersFromFile(const string& filename);
	static bool SaveUserIntoFile(const string& filename, const string& name, const string& password, const string& role);

};