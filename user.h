#ifndef LABORATORY_USER_H
#define LABORATORY_USER_H
#include <vector>
#include <movie.h>

class user {
private:
    std::string username;
    std::string password;
    bool hasAdministratorRights = false;
    std::vector<movie> Watchlist;
public:
    user(std::string username, std::string password, bool hasAdministratorRights = false);
    user(std::string username, std::string password, bool hasAdministratorRights, const std::vector<movie>& watchlist);
    ~user();

    std::string getUsername() const;
    std::string getPassword() const;
    bool getHasAdministratorRights() const;
    std::vector<movie> getWatchlist() const;

    void setUsername(std::string username);
    void setPassword(std::string password);
    void setHasAdministratorRights(bool hasAdministratorRights);
    void setWatchlist(const std::vector<movie>& newWatchlist);


    void addToWatchlist(const movie& movie);
    void removeFromWatchlist(const std::string& movieTitle);
    void seeWatchlist() const;


    bool checkPassword(const std::string& inputPassword) const;
};


#endif //LABORATORY_USER_H