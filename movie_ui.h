#ifndef MOVIE_UI_H
#define MOVIE_UI_H

#include "movie_service.h"
#include "user.h"
#include <string>

class MovieUI {
private:
    MovieService& movieService;
    static int getInt(const std::string& prompt, int min, int max) ;
    static std::string getString(const std::string& prompt);
    static bool getYesNo(const std::string& prompt) ;
    movie createMovieFromInput() const;

public:
    explicit MovieUI(MovieService& service);
    ~MovieUI() = default;
    void displayMainMenu( user* currentUser) const;
    void displayMovieDetails(const std::string& title) const;
    void displayAllMovies() const;
    void searchAndDisplayMovies() const;

    void addMovieUI( user* currentUser) const;
    void editMovieUI( user* currentUser) const;
    void deleteMovieUI( user* currentUser) const;
    void addCommentUI( user* currentUser) const;

    static void viewWatchlist( user* currentUser) ;
    void addToWatchlist(user* currentUser) const;
    static void removeFromWatchlist( user* currentUser) ;
};

#endif