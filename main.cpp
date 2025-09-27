#include "movie_ui.h"
#include "movie_service.h"
#include "movie_repository.h"
#include "comment_manager.h"
#include "user_manager.h"
#include <iostream>
#include <memory>
#include <limits>

class Application {
private:
    MovieRepository movieRepository;
    CommentManager commentManager;
    MovieService movieService;
    UserManager userManager;
    MovieUI movieUI;
    user* currentUser;

public:
    Application() 
        : movieService(movieRepository, commentManager),
          movieUI(movieService),
          currentUser(nullptr) {}

    void run() {
        std::cout << "=== Movie Database Management System ===\n";
        std::cout << "Welcome to the Movie Database!\n\n";

        while (true) {
            if (!currentUser) {
                displayLoginMenu();
            } else {
                movieUI.displayMainMenu(currentUser);
                if (currentUser) {
                    std::cout << "\nReturn to login? (y/n): ";
                    char choice;
                    std::cin >> choice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (choice == 'y' || choice == 'Y') {
                        UserManager::logout(currentUser);
                    } else {
                        std::cout << "Goodbye!\n";
                        break;
                    }
                }
            }
        }
    }

private:
    void displayLoginMenu() {
        while (true) {
            std::cout << "\n=== Main Menu ===\n";
            std::cout << "1. Login\n";
            std::cout << "2. Register\n";
            std::cout << "3. Exit\n";
            
            int choice;
            std::cout << "Choose option: ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    login();
                    if (currentUser) return;
                    break;
                case 2:
                    registerUser();
                    break;
                case 3:
                    std::cout << "Goodbye!\n";
                    exit(0);
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
        }
    }

    void login() {
        std::cout << "\n=== Login ===\n";
        std::string username, password;
        
        std::cout << "Username: ";
        std::getline(std::cin, username);
        
        std::cout << "Password: ";
        std::getline(std::cin, password);

        currentUser = userManager.login(username, password);
        
        if (!currentUser) {
            std::cout << "Login failed. Please check your credentials.\n";
        }
    }

    void registerUser() {
        std::cout << "\n=== Register ===\n";
        std::string username, password;
        
        std::cout << "Choose username: ";
        std::getline(std::cin, username);
        
        std::cout << "Choose password: ";
        std::getline(std::cin, password);

        if (userManager.registerUser(username, password)) {
            std::cout << "Registration successful! You can now login.\n";
        } else {
            std::cout << "Registration failed. Username may already exist.\n";
        }
    }

};

int main() {
    try {
        Application app;
        app.run();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return 1;
    }
    
    return 0;
}