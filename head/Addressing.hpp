#include <string>
using namespace std;
#include <memory>
#include <map>
class Addressing {
    private:
    int static adress_index;
    static int next_adress_index;
    string row;
    string cell;
    string storage_area;
    static map<int, shared_ptr<Addressing>> addres;
    public:
    Addressing(string storage_area, string row, string cell) : storage_area(storage_area), row(row), cell(cell) {};
    shared_ptr<Addressing> makeAdress() const;
    string getRow() const;
    string getCell() const;
    string getStorage_Area() const;
    int getIndex() const;
    shared_ptr<Addressing> Addressing::getAddressing(const int& adress_index) const;
};