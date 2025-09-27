#include "movie_repository.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>

MovieRepository::MovieRepository() {
    loadFromFile();
}

void MovieRepository::loadFromFile() {
    std::ifstream file(moviesFile);
    if (!file.is_open()) {
        std::cout << "Movies file not found. Creating new one.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, genreStr, director, country, plot;
        int year, budget, gross, runningTime;

        if (std::getline(iss, title, '|') &&
            std::getline(iss, genreStr, '|') &&
            std::getline(iss, director, '|') &&
            std::getline(iss, country, '|') &&
            iss >> year && iss.ignore() &&
            iss >> budget && iss.ignore() &&
            iss >> gross && iss.ignore() &&
            iss >> runningTime && iss.ignore() &&
            std::getline(iss, plot)) {

            Genre genre = stringToGenre(genreStr);
            movies.push_back(std::make_unique<movie>(title, genre, director, country, year, budget, gross, runningTime, plot));
        }
    }
    file.close();
}

void MovieRepository::saveToFile() const {
    std::ofstream file(moviesFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot save movies to file!\n";
        return;
    }

    for (const auto& moviePtr : movies) {
        file << moviePtr->getTitle() << "|"
             << fromEnumToString(moviePtr->getGenre()) << "|"
             << moviePtr->getDirector() << "|"
             << moviePtr->getCountry() << "|"
             << moviePtr->getYear() << "|"
             << moviePtr->getBudget() << "|"
             << moviePtr->getGross() << "|"
             << moviePtr->getRunningTime() << "|"
             << moviePtr->getPlot() << "\n";
    }
    file.close();
}

bool MovieRepository::addMovie(std::unique_ptr<movie> movie) {
    if (!movie || movieExists(movie->getTitle())) {
        return false;
    }
    
    movies.push_back(std::move(movie));
    saveToFile();
    return true;
}

bool MovieRepository::deleteMovie(const std::string& title) {
    auto it = std::find_if(movies.begin(), movies.end(),
        [&title](const std::unique_ptr<movie>& m) {
            return m->getTitle() == title;
        });

    if (it != movies.end()) {
        movies.erase(it);
        saveToFile();
        return true;
    }
    return false;
}

movie* MovieRepository::findMovieByTitle(const std::string& title) const {
    auto it = std::find_if(movies.begin(), movies.end(),
        [&title](const std::unique_ptr<movie>& m) {
            return m->getTitle() == title;
        });
    return it != movies.end() ? it->get() : nullptr;
}

std::vector<movie*> MovieRepository::searchMovies(const std::string& searchTerm) const {
    std::vector<movie*> results;
    std::string lowerTerm = searchTerm;
    std::transform(lowerTerm.begin(), lowerTerm.end(), lowerTerm.begin(), ::tolower);

    for (const auto& moviePtr : movies) {
        std::string title = moviePtr->getTitle();
        std::string director = moviePtr->getDirector();
        std::string genre = fromEnumToString(moviePtr->getGenre());

        std::transform(title.begin(), title.end(), title.begin(), ::tolower);
        std::transform(director.begin(), director.end(), director.begin(), ::tolower);
        std::transform(genre.begin(), genre.end(), genre.begin(), ::tolower);

        if (title.find(lowerTerm) != std::string::npos ||
            director.find(lowerTerm) != std::string::npos ||
            genre.find(lowerTerm) != std::string::npos) {
            results.push_back(moviePtr.get());
        }
    }
    return results;
}

std::vector<movie*> MovieRepository::getAllMovies() const {
    std::vector<movie*> result;
    result.reserve(movies.size());
for (const auto& moviePtr : movies) {
        result.push_back(moviePtr.get());
    }
    return result;
}

size_t MovieRepository::getMovieCount() const {
    return movies.size();
}

bool MovieRepository::movieExists(const std::string& title) const {
    return findMovieByTitle(title) != nullptr;
}
