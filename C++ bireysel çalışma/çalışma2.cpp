#include <iostream>
#include <string>

int main() {
    std::string username = "admin";
    std::string password = "12345";

    std::string inputUsername;
    std::string inputPassword;

    std::cout << "Username: ";
    std::cin >> inputUsername;
    std::cout << "Password: ";
    std::cin >> inputPassword;

    if (inputUsername == username && inputPassword == password) {
        std::cout << "Login successful!" << std::endl;
    } else {
        std::cout << "Invalid username or password." << std::endl;
    }

    return 0;
}