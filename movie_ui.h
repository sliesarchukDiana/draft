#ifndef MOVIE_UI_H
#define MOVIE_UI_H

#include "movie_service.h"
#include "user.h"
#include <string>

class MovieUI {
private:
    MovieService& movieService;

    // Вспомогательные методы для ввода
    static int getInt(const std::string& prompt, int min, int max) ;

    static std::string getString(const std::string& prompt);
    static bool getYesNo(const std::string& prompt) ;
    movie createMovieFromInput() const;

public:
    explicit MovieUI(MovieService& service);
    ~MovieUI() = default;

    // Основные UI методы
    void displayMainMenu(const user* currentUser) const;
    void displayMovieDetails(const std::string& title) const;
    void displayAllMovies() const;
    void searchAndDisplayMovies() const;

    // Операции требующие аутентификации
    void addMovieUI(const user* currentUser) const;
    void editMovieUI(const user* currentUser) const;
    void deleteMovieUI(const user* currentUser) const;
    void addCommentUI(const user* currentUser) const;

    // Методы для работы с watchlist
    static void viewWatchlist(const user* currentUser) ;
    void addToWatchlist(const user* currentUser) const;
    static void removeFromWatchlist(const user* currentUser) ;
};

#endif