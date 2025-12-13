#include "UserSystem.hpp"
#include "Employee.hpp"
#include "Manager.hpp"
#include "StoreKeeper.hpp"
#include "Client.hpp"
#include <iostream>

using namespace std;

int main() {
    UserSystem* user = nullptr;
    int choice;
    cout << "Выбирете режим работы: "<< endl;
    cin >> choice;
    switch(choice){
    case 1: user = Client::login(); break;
    case 2: user = Administrator::loginEmployee("Администратор"); break;
    case 3: user = Manager::loginEmployee("Менеджер"); break;
    case 4: user = StoreKeeper::loginEmployee("Кладовщик"); break;
    }

    if(user) {
        user->showMenu();
        delete user;
    }
}