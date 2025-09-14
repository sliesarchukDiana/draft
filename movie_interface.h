#ifndef MOVIE_INTERFACE_H
#define MOVIE_INTERFACE_H
#include <vector>
#include <memory>
#include <string>
#include "movie.h"

class MovieInterface {
public:
    virtual ~MovieInterface() = default;
    virtual void run() = 0;

protected:
    static int getInt(const std::string& prompt, int min, int max);
    static std::string getString(const std::string& prompt);
    static bool getYesNo(const std::string& prompt);
    void loadMovies();
    void saveMovies() const;
    std::vector<std::unique_ptr<movie>> movies;
};

#endif