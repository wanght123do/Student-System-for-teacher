#include "studentSystemTool.h"
#include <vector>
#include <string>


int main() {
    std::cout << "Welcome to the Student Management System\n";
    Sleep(3000);
    system("cls");
    while (true) {
        std::cout << "1. Sign In\n2. Sign Up\n3. Exit\nChoose an option: ";
        std::string choice;
        std::cin >> choice;
        system("cls");
        if (choice == "1") {
            std::string id, password;
            std::cout << "Enter your ID: ";
            std::cin >> id;
            std::cout << "Enter your password: ";
            std::cin >> password;
            signIn(id, password);
            system("cls");
        } else if (choice == "2") {
            system("cls");
            signUp();
        } else if (choice == "3") {
            std::cout << "Exiting the system. Goodbye!\n";
            Sleep(2000);
            system("cls");
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
            system("cls");
        }
    }
    return 0;
}