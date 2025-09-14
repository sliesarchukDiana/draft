#include "sciFy.h"
#include <iostream>
#include <utility>

sciFy::sciFy()
    : movie("Unknown sci-fi", "Unknown", "Unknown", 0, 0), timePeriod(TimePeriod::NoInfo) {
    std::cout << "Default constructor was called for " << getTitle() << " of class sci-fi" << std::endl;
}

sciFy::sciFy(std::string title, std::string director, std::string plot, int runningTime, int budget, TimePeriod period)
    : movie(std::move(title), std::move(director), std::move(plot), runningTime, budget), timePeriod(period) {
    std::cout << "Parameterized constructor was called for " << getTitle() << " of class sci-fi" << std::endl;
}

sciFy::sciFy(const sciFy& other): movie(other), timePeriod(other.timePeriod) {
    std::cout << "Copy constructor was called for " << getTitle() << " of class sci-fi" << std::endl;
}

sciFy::sciFy(sciFy&& other) noexcept: movie(std::move(other)), timePeriod(other.timePeriod)
{
    other.timePeriod = TimePeriod::NoInfo;
    std::cout << "Move constructor was called for " << getTitle() << " of class sci-fi\n";
}

sciFy::~sciFy() {
    std::cout << "The destructor was called for " << getTitle() << " of class sci-fi" << std::endl;
}

TimePeriod sciFy::getTimePeriod() const noexcept {
    return timePeriod;
}

void sciFy::setTimePeriod(TimePeriod period) {
    timePeriod = period;
}

std::string sciFy::timePeriodToString(TimePeriod period) {
    switch(period) {
        case TimePeriod::NoInfo: return "No Info";
        case TimePeriod::NearFuture: return "Near Future";
        case TimePeriod::Dystopian: return "Dystopian";
        case TimePeriod::Cyberpunk: return "Cyberpunk";
        case TimePeriod::SpaceAge: return "Space Age";
        case TimePeriod::AlternateHistory: return "Alternate History";
        default: return "Unknown";
    }
}

void sciFy::displayDetails() const {
    std::cout << "Sci-Fi Movie: " << getTitle()
              << "\nDirector: " << getDirector()
              << "\nPlot: " << getPlot()
              << "\nRunning Time: " << getRunningTime() << " minutes"
              << "\nBudget: $" << getBudget()
              << "\nTime Period: " << timePeriodToString(timePeriod) << '\n';
}