#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "user.h"
#include <unordered_map>
#include <memory>
#include <string>

class UserManager {
private:
    std::unordered_map<std::string, std::unique_ptr<user>> users;
    const std::string accountsFile = "accounts.txt";

    void loadUsersFromFile();
    void saveUsersToFile() const;

    static std::string serializeUser(const user& user);

    static user* deserializeUser(const std::string& userData);

public:
    UserManager();
    ~UserManager() = default;

    bool registerUser(const std::string& username, const std::string& password, bool isAdmin = false);
    user* login(const std::string& username, const std::string& password);
    user* findUser(const std::string& username);
    bool deleteUser(const std::string& username);
    void listAllUsers() const;
    bool userExists(const std::string& username) const;
    static void logout(user*& currentUser);
};

#endif