#include "thriller.h"
#include "movie.h"
#include <iostream>
#include <utility>

thriller::thriller() : movie("Unknown thriller", "Unknown", "Unknown", 0, 0), isChildFriendly(false) {
    std::cout << "Default constructor was called for " << getTitle() << " of class thriller" << std::endl;
}

thriller::thriller(std::string title, std::string director, std::string plot, int runningTime, int budget, bool childFriendly)
    : movie(std::move(title), std::move(director), std::move(plot), runningTime, budget), isChildFriendly(childFriendly) {
    std::cout << "Parameterized constructor was called for " << getTitle() << " of class thriller" << std::endl;
}

thriller::thriller(const thriller& other)
    : movie(other), isChildFriendly(other.isChildFriendly) {
    std::cout << "Copy constructor was called for " << getTitle() << " of class thriller" << std::endl;
}

thriller::thriller(thriller&& other) noexcept
    : movie(std::move(other)){
    std::cout << "Move constructor was called for " << getTitle() << " of class thriller" << std::endl;
}

thriller::~thriller() {
    std::cout << "The destructor was called for " << getTitle() << " of class thriller" << std::endl;
}


bool thriller::getIsChildFriendly() const {
    return isChildFriendly;
}
void thriller::setIsChildFriendly(bool newIsChildFriendly) {
    isChildFriendly = newIsChildFriendly;
}

std::string thriller::isChildFriendlyToMessage(bool childFriendly) {
    if (childFriendly) {
        return "is child friendly";
    } else {
        return "for adult audience only";
    }
}

void thriller::displayDetails() const {
    std::cout << "Thriller Movie: " << getTitle()
              << "\nDirector: " << getDirector()
              << "\nPlot: " << getPlot()
              << "\nRunning Time: " << getRunningTime() << " minutes"
              << "\nBudget: " << getBudget() <<"$"
              << "\nAge limit: " << isChildFriendlyToMessage(isChildFriendly) << std::endl;
}
