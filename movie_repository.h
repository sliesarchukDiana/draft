#ifndef MOVIE_REPOSITORY_H
#define MOVIE_REPOSITORY_H

#include "movie.h"
#include <vector>
#include <memory>
#include <string>

class MovieRepository {
private:
    std::vector<std::unique_ptr<movie>> movies;
    const std::string moviesFile = "movies.txt";

    void loadFromFile();
    void saveToFile() const;

public:
    MovieRepository();
    ~MovieRepository() = default;

    bool addMovie(std::unique_ptr<movie> movie);
    bool deleteMovie(const std::string& title);
    movie* findMovieByTitle(const std::string& title) const;

    std::vector<movie*> searchMovies(const std::string& searchTerm) const;
    std::vector<movie*> getAllMovies() const;
    size_t getMovieCount() const;

    bool movieExists(const std::string &title) const;
};

#endif