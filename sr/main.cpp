#include "UserSystem.hpp"
#include <locale>

int main() {
    setlocale(LC_ALL, "Russian");

    UserSystem system;
    system.run();

    return 0;
}