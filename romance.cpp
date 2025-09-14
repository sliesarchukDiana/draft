#include "romance.h"
#include <iostream>
#include <utility>

romance::romance() : movie("Unknown action", "Unknown director", "Unknown country", 0, 0, 0, 0, "No info"), happyEnding(true) {
    std::cout << "Default constructor was called for " << getTitle() << " of class romance" << std::endl;
}

romance::romance(std::string t, std::string d, std::string c, int y, int b, int g, int rt, std:: string p, bool happyEnding)
    : movie(std::move(t), std::move(d), std::move(c), y, b, g, rt, std::move(p)), happyEnding(happyEnding) {
    std::cout << "Parameterized constructor was called for " << getTitle() << " of class romance" << std::endl;
}

romance::romance(const romance& other)
    : movie(other), happyEnding(other.happyEnding) {
    std::cout << "Copy constructor was called for " << getTitle() << " of class romance" << std::endl;
}

romance::romance(romance&& other) noexcept
    : movie(std::move(other)){
    std::cout << "Move constructor was called for " << getTitle() << " of class romance" << std::endl;
}

romance::~romance() {
    std::cout << "The destructor was called for " << getTitle() << " of class romance" << std::endl;
}


bool romance::getHappyEnding() const {
    return happyEnding;
}
void romance::setHappyEnding(bool newHappyEnding) {
    happyEnding = newHappyEnding;
}

std::string romance::happyEndingToMessage(bool ending) {
    if (ending) {
        return "Happy ending";
    } else {
        return "Sad ending";
    }
}

void romance::displayDetails() const {
    std::cout << "Title: " << getTitle() << "\n"
    << "Director: " << getDirector() << "\n"
    << "Country: " << getCountry() << "\n"
    << "Year: " << getYear() << "\n"
    << "Budget: " << getBudget() << "\n"
    << "Gross: " << getGross() <<"\n"
    << "Running Time: " << getRunningTime() << " minutes\n"
    << "Plot: " << getPlot() <<"\n"
    << "Ending: " << happyEndingToMessage(happyEnding) << std::endl;
}
