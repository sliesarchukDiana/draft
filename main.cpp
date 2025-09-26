#include <iostream>
#include "user_manager.h"

void showMenu() {
    std::cout << "\n=== User Management System ===\n";
    std::cout << "1. Register\n";
    std::cout << "2. Login\n";
    std::cout << "3. List Users\n";
    std::cout << "4. Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    UserManager userManager;
    user* currentUser = nullptr;

    while (true) {
        showMenu();

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Очистка буфера

        switch (choice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                userManager.registerUser(username, password);
                break;
            }

            case 2: {
                if (currentUser) {
                    std::cout << "You are already logged in as: " << currentUser->getUsername() << "\n";
                    break;
                }

                std::string username, password;
                std::cout << "Enter username: ";
                std::getline(std::cin, username);
                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                currentUser = userManager.login(username, password);
                break;
            }

            case 3: {
                userManager.listAllUsers();
                break;
            }

            case 4: {
                std::cout << "Goodbye!\n";
                return 0;
            }

            default: {
                std::cout << "Invalid choice!\n";
                break;
            }
        }
    }

    return 0;
}