#include "sciFi.h"
#include <iostream>
#include <utility>

sciFy::sciFy()
    : movie("Unknown action", "Unknown director", "Unknown country", 0, 0, 0, 0, "No info"), timePeriod(TimePeriod::NoInfo) {
    std::cout << "Default constructor was called for " << getTitle() << " of class sci-fi" << std::endl;
}

sciFy::sciFy(std::string t, std::string d, std::string c, int y, int b, int g, int rt, std:: string p, TimePeriod period)
    : movie(std::move(t), std::move(d), std::move(c), y, b, g, rt, std::move(p)), timePeriod(period) {
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
    std::cout << "Title: " << getTitle() << "\n"
    << "Subgenre: " << timePeriodToString(timePeriod) << "\n"
    << "Director: " << getDirector() << "\n"
    << "Country: " << getCountry() << "\n"
    << "Year: " << getYear() << "\n"
    << "Budget: " << getBudget() << "\n"
    << "Gross: " << getGross() <<"\n"
    << "Running Time: " << getRunningTime() << " minutes\n"
    << "Plot: " << getPlot() << std::endl;
}