#include "movie.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <utility>

int movie::count = 0;

movie::movie()
    : title("Unknown movie"), genre(Genre::noInfo), director("Unknown director"), country("Unknown country"), year (0), budget(0), gross(0), runningTime(0), plot("No info")  {
    std::cout << "Default constructor was called for " << title<<" of parent class movie"<< std::endl;
    count++;
}
movie::movie(std::string t,  Genre genre, std::string d, std::string c, int y, int b, int g, int rt, std:: string p)
    : title(std::move(t)), genre(genre), director(std::move(d)), country(std::move(c)), year(y), budget(b), gross(g), runningTime(rt), plot(std::move(p)) {
    std::cout << "Parameterized constructor was called for " << title <<" of parent class movie"<< std::endl;
    count++;
}

movie::movie(const movie& other)
    : title(other.title), genre(other.genre), director(other.director), country(other.country), year(other.year), budget(other.budget), gross(other.gross), runningTime(other.runningTime), plot(other.plot) {
    count++;
    std::cout << "Copy constructor was called for " << title <<" of parent class movie"<< std::endl;
}
movie& movie::operator=(const movie& other) { //copy assignment operator//
    if (this != &other) {
        title = other.title;
        genre = other.genre;
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

movie& movie::operator=(movie&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        genre = other.genre;
        director = std::move(other.director);
        country = std::move(other.country);
        year = other.year;
        budget = other.budget;
        gross = other.gross;
        runningTime = other.runningTime;
        plot = std::move(other.plot);
    }
    return *this;
}

movie::movie(movie&& other) noexcept
    : title(std::move(other.title)),
      genre(other.genre),
      director(std::move(other.director)),
      country(std::move(other.country)),
      year(other.year),
      budget(other.budget),
      gross(other.gross),
      runningTime(other.runningTime),
      plot(std::move(other.plot))
 {
    std::cout << "Move constructor was called for " << title<< std::endl;
}

movie::~movie() {
    std::cout << "The destructor was called for " << title<< std::endl;
    count--;
}

std::string movie::getTitle() const {
    return title;
}
Genre movie::getGenre() const {
    return genre;
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
void movie::setGenre(Genre newGenre) {
    genre = newGenre;
}
void movie::setDirector(const std::string& newDirector) {
    director = newDirector;
}
void movie::setCountry(const std::string& newCountry) {
    country = newCountry;
}
void movie::setYear(int newYear) {
    if (newYear > 1888)
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

std::string fromEnumToString(Genre genre) {
    switch (genre) {
        case (Genre::drama): return "Drama";
        case (Genre::romance):  return "Romance";
        case (Genre::thriller):  return "Thriller";
        case(Genre::scienceFiction):  return "Science Fiction";
        case(Genre::crime): return "Crime";
        case(Genre::horror):  return "Horror";
        case(Genre::action):  return "Action";
        case(Genre::western):  return "Western";
        case(Genre::mystery):  return "Mystery";
        case(Genre::historical):  return "Historical";
        case(Genre::comedy):  return "Comedy";
        case(Genre::fantasy):  return "Fantasy";
        case(Genre::animation):  return "Animation";
        case(Genre::adventure):  return "Adventure";
        case(Genre::documentary):  return "Documentary";
        default : return "No info";


    }
}

Genre stringToGenre(const std::string& genreStr) {
    static const std::unordered_map<std::string, Genre> genreMap = {
        {"drama", Genre::drama},
        {"romance", Genre::romance},
        {"thriller", Genre::thriller},
        {"science fiction", Genre::scienceFiction},
        {"sciencefiction", Genre::scienceFiction},
        {"sci-fi", Genre::scienceFiction},
        {"crime", Genre::crime},
        {"horror", Genre::horror},
        {"action", Genre::action},
        {"western", Genre::western},
        {"mystery", Genre::mystery},
        {"historical", Genre::historical},
        {"comedy", Genre::comedy},
        {"fantasy", Genre::fantasy},
        {"animation", Genre::animation},
        {"adventure", Genre::adventure},
        {"documentary", Genre::documentary},
        {"noinfo", Genre::noInfo},
        {"no info", Genre::noInfo},
        {"unknown", Genre::noInfo}
    };
    std::string lowerStr = genreStr;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    lowerStr.erase(0, lowerStr.find_first_not_of(' '));
    lowerStr.erase(lowerStr.find_last_not_of(' ') + 1);
    auto it = genreMap.find(lowerStr);
    if (it != genreMap.end()) {
        return it->second;
    }
    for (const auto& pair : genreMap) {
        if (lowerStr.find(pair.first) != std::string::npos) {
            return pair.second;
        }
    }

    return Genre::noInfo;
}

std::ostream& operator<<(std::ostream& os, const movie& t) {
    os << "Title: " << t.title << "\n"
    << "Genre: " << fromEnumToString(t.genre) << "\n"
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
    std::getline(is >> std::ws, t.title);
    std::cout << "Enter genre (Drama, Comedy, Action, etc.): ";
    std::string genreInput;
    std::getline(is, genreInput);
    t.genre = stringToGenre(genreInput);
    if (t.genre == Genre::noInfo && !genreInput.empty()) {
        std::cout << "Genre not recognized. Available genres: Drama, Comedy, Action, "
                  << "Romance, Thriller, Science Fiction, Crime, Horror, Western, "
                  << "Mystery, Historical, Fantasy, Animation, Adventure, Documentary\n";
    }
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
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter plot: ";
    std::getline(is, t.plot);

    return is;
}