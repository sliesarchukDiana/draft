#include "movie.h"
#include <iostream>
#include <string>
#include <utility>

int movie::count = 0;

movie::movie()
    : title("Unknown movie"), director("Unknown director"), country("Unknown country"), year (0), budget(0), gross(0), runningTime(0), plot("No info")  {
    std::cout << "Default constructor was called for " << title<<" of parent class movie"<< std::endl;
    count++;
}
movie::movie(std::string t, std::string d, std::string c, int y, int b, int g, int rt, std:: string p)
    : title(std::move(t)), director(std::move(d)), country(std::move(c)), year(y), budget(b), gross(g), runningTime(rt), plot(std::move(p)) {
    std::cout << "Parameterized constructor was called for " << title <<" of parent class movie"<< std::endl;
    count++;
}

movie::movie(const movie& other)
    : title(other.title), director(other.director), country(other.country), year(other.year), budget(other.budget), gross(other.gross), runningTime(other.runningTime), plot(other.plot) {
    count++;
    std::cout << "Copy constructor was called for " << title <<" of parent class movie"<< std::endl;
}
movie& movie::operator=(const movie& other) { //copy assignment operator//
    if (this != &other) {
        title = other.title;
        director = other.director;
        country = other.country;
        year = other.year;
        budget = other.budget;
        gross = other.gross;
        runningTime = other.runningTime;
        plot = other.plot;
    }
    return *this;
}
movie::movie(movie&& other) noexcept
    : title(std::move(other.title)),
      director(std::move(other.director)),
      country(std::move(other.country)),
      year(other.year),
      budget(other.budget),
      gross(other.gross),
      runningTime(other.runningTime),
      plot(std::move(other.plot))
 {
    count++;
    std::cout << "Move constructor was called for " << title <<" of parent class movie"<< std::endl;
}

movie::~movie() {
    std::cout << "The destructor was called for " << title <<" of parent class movie"<< std::endl;
    count--;
}

std::string movie::getTitle() const {
    return title;
}
std::string movie::getDirector() const {
    return director;
}
std::string movie::getCountry() const {
    return country;
}
int movie::getYear() const {
    return year;
}
int movie::getBudget() const {
    return budget;
}
int movie::getGross() const {
    return gross;
}
int movie::getRunningTime() const {
    return runningTime;
}
std::string movie::getPlot() const {
    return plot;
}


void movie::setTitle(const std::string& newTitle) {
    title = newTitle;
}
void movie::setDirector(const std::string& newDirector) {
    director = newDirector;
}
void movie::setCountry(const std::string& newCountry) {
    country = newCountry;
}
void movie::setYear(int newYear) {
    if (newYear > 0) //Я хз якє тут обмеження ліпити//
    {
        year = newYear;
    }
}
void movie::setBudget(int newBudget) {
    if (newBudget > 0) {
        budget = newBudget;
    }
}
void movie::setGross(int newGross) {
    if (newGross > 0) {
        gross = newGross;
    }
}
void movie::setRunningTime(int newRunningTime) {
    if (newRunningTime > 0) {
        runningTime = newRunningTime;
    }
}
void movie::setPlot(const std::string& newPlot) {
    plot = newPlot;
}




int movie::getObjectCount() {
    return count;
}

std::ostream& operator<<(std::ostream& os, const movie& t) {
    os << "Title: " << t.title << "\n"
    << "Director: " << t.director << "\n"
    << "Country: " << t.country << "\n"
    << "Year: " << t.year << "\n"
    << "Budget: " << t.budget << "\n"
    <<" Gross: " << t.gross <<"\n"
    << "Running Time: " << t.runningTime << " minutes\n"
    << "Plot: " << t.plot << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, movie& t) {
    std::cout << "Enter title: ";
    std::getline(is, t.title);
    std::cout << "Enter director: ";
    std::getline(is, t.director);
    std::cout << "Enter country: ";
    std::getline(is, t.country);
    std::cout << "Enter year: ";
    is >> t.year;
    std::cout << "Enter budget: ";
    is >> t.budget;
    std::cout << "Enter gross: ";
    is >> t.gross;
    std::cout << "Enter running time: ";
    is >> t.runningTime;
    std::cout << "Enter plot: ";
    std::getline(is, t.plot);
    return is;
}