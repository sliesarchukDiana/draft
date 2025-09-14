#include "romance.h"
#include <iostream>
#include <utility>

romance::romance() : movie("Unknown romance", "Unknown", "Unknown", 0, 0), happyEnding(true) {
    std::cout << "Default constructor was called for " << getTitle() << " of class romance" << std::endl;
}

romance::romance(std::string title, std::string director, std::string plot, int runningTime, int budget, bool happyEnding)
    : movie(std::move(title), std::move(director), std::move(plot), runningTime, budget), happyEnding(happyEnding) {
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
    std::cout << "Romance Movie: " << getTitle()
              << "\nDirector: " << getDirector()
              << "\nPlot: " << getPlot()
              << "\nRunning Time: " << getRunningTime() << " minutes"
              << "\nBudget: " << getBudget() <<"$"
              << "\nEnding: " << happyEndingToMessage(happyEnding) << std::endl;
}
