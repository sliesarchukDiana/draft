#include "thriller.h"
#include "movie.h"
#include <iostream>
#include <utility>

thriller::thriller() : movie("Unknown action", "Unknown director", "Unknown country", 0, 0, 0, 0, "No info"), isChildFriendly(false) {
    std::cout << "Default constructor was called for " << getTitle() << " of class thriller" << std::endl;
}

thriller::thriller(std::string t, std::string d, std::string c, int y, int b, int g, int rt, std:: string p, bool childFriendly)
    : movie(std::move(t), std::move(d), std::move(c), y, b, g, rt, std::move(p)), isChildFriendly(childFriendly) {
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
    std::cout << "Title: " << getTitle() << "\n"
    << "Director: " << getDirector() << "\n"
    << "Country: " << getCountry() << "\n"
    << "Year: " << getYear() << "\n"
    << "Budget: " << getBudget() << "\n"
    << "Gross: " << getGross() <<"\n"
    << "Running Time: " << getRunningTime() << " minutes\n"
    << "Plot: " << getPlot() <<"\n"
    << "Age limit: " << isChildFriendlyToMessage(isChildFriendly) << std::endl;
}
