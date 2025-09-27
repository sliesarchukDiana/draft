#include "user_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

UserManager::UserManager() {
    loadUsersFromFile();
    if (users.empty()) {
        registerUser("admin", "admin123", true);
        std::cout << "Default admin account created: admin/admin123\n";
    }
}

void UserManager::loadUsersFromFile() {
    std::ifstream file(accountsFile);
    if (!file.is_open()) {
        std::cout << "Accounts file not found. Creating new one.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        user* newUser = deserializeUser(line);
        if (newUser) {
            users[newUser->getUsername()] = std::unique_ptr<user>(newUser);
        }
    }
    file.close();
    std::cout << "Loaded " << users.size() << " users from file.\n";
}

void UserManager::saveUsersToFile() const {
    std::ofstream file(accountsFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot save users to file!\n";
        return;
    }

    for (const auto& pair : users) {
        const std::unique_ptr<user>& userPtr = pair.second;
        file << serializeUser(*userPtr) << "\n";
    }
    file.close();
}

std::string UserManager::serializeUser(const user& user) {
    std::ostringstream oss;
    oss << user.getUsername() << "|"
        << user.getPassword() << "|"
        << (user.getHasAdministratorRights() ? "1" : "0");
    return oss.str();
}

user* UserManager::deserializeUser(const std::string& userData) {
    std::istringstream iss(userData);
    std::string username, password, adminStr;

    if (std::getline(iss, username, '|') &&
        std::getline(iss, password, '|') &&
        std::getline(iss, adminStr)) {

        bool isAdmin = (adminStr == "1");
        return new user(username, password, isAdmin);
    }
    return nullptr;
}

bool UserManager::registerUser(const std::string& username, const std::string& password, bool isAdmin) {
    if (userExists(username)) {
        std::cout << "Error: Username '" << username << "' already exists!\n";
        return false;
    }

    if (username.empty() || password.empty()) {
        std::cout << "Error: Username and password cannot be empty!\n";
        return false;
    }

    users[username] = std::make_unique<user>(username, password, isAdmin);
    saveUsersToFile();
    std::cout << "User '" << username << "' registered successfully!\n";
    return true;
}

user* UserManager::login(const std::string& username, const std::string& password) {
    auto it = users.find(username);
    if (it != users.end() && it->second->checkPassword(password)) {
        std::cout << "Login successful! Welcome, " << username << "!\n";
        return it->second.get();
    }
    std::cout << "Error: Invalid username or password!\n";
    return nullptr;
}

user* UserManager::findUser(const std::string& username) {
    auto it = users.find(username);
    return it != users.end() ? it->second.get() : nullptr;
}

bool UserManager::deleteUser(const std::string& username) {
    if (users.erase(username) > 0) {
        saveUsersToFile();
        std::cout << "User '" << username << "' deleted successfully!\n";
        return true;
    }
    std::cout << "Error: User '" << username << "' not found!\n";
    return false;
}

void UserManager::listAllUsers() const {
    if (users.empty()) {
        std::cout << "No users registered.\n";
        return;
    }

    std::cout << "=== Registered Users ===\n";
    for (const auto& pair : users) {
        const std::string& username = pair.first;
        const std::unique_ptr<user>& userPtr = pair.second;
        std::cout << "- " << username
                  << " (" << (userPtr->getHasAdministratorRights() ? "Admin" : "User") << ")\n";
    }
}

bool UserManager::userExists(const std::string& username) const {
    return users.find(username) != users.end();
}

void UserManager::logout(user*& currentUser) {
    if (currentUser) {
        std::cout << "Goodbye, " << currentUser->getUsername() << "!\n";
        currentUser = nullptr;
    }
}