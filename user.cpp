#include "user.h"
#include <vector>
#include <algorithm>

user::user(std::string u, std::string p, bool adminRights)
    : username(std::move(u)), password(std::move(p)), hasAdministratorRights(adminRights) {}

user::user(std::string u, std::string p, bool hasAdministratorRights, const std::vector<movie>& watchlist) :
username(std::move(u)), password(std::move(p)), hasAdministratorRights(hasAdministratorRights), Watchlist(watchlist){};

user::~user() {
    std::cout << "Destroyed user " << username << "\n";
};

std::string user::getUsername() const {
    return username;
}
std::string user::getPassword() const {
    return password;
}
bool user::getHasAdministratorRights() const {
    return hasAdministratorRights;
}
std::vector<movie> user::getWatchlist() const {
    return Watchlist;
}

void user::setUsername(std::string newUsername) {
    this->username = std::move(newUsername);
}
void user::setPassword(std::string newPassword) {
    this->password = std::move(newPassword);
}
void user::setHasAdministratorRights(bool newHasAdministratorRights) {
    this->hasAdministratorRights = newHasAdministratorRights;
}
void user::setWatchlist(const std::vector<movie>& newWatchlist) {
    Watchlist = newWatchlist;
}

void user::addToWatchlist(const movie& movie) {
    Watchlist.push_back(movie);
}


void user::removeFromWatchlist(const std::string& movieTitle) {
    Watchlist.erase(
        std::remove_if(Watchlist.begin(), Watchlist.end(),
            [&movieTitle](const movie& m) {
                return m.getTitle() == movieTitle;
            }),
        Watchlist.end()
    );
}


void user::seeWatchlist() const {
    if (Watchlist.empty()) {
        std::cout << "Your watchlist is empty.\n";
        return;
    }

    std::cout << "=== Your Watchlist ===\n";
    for (size_t i = 0; i < Watchlist.size(); ++i) {
        std::cout << i + 1 << ". " << Watchlist[i].getTitle()
                  << " (" << Watchlist[i].getYear() << ")\n";
    }
}

bool user::checkPassword(const std::string& inputPassword) const {
    return password == inputPassword;
}
