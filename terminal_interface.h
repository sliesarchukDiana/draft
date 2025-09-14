#ifndef TERMINAL_INTERFACE_H
#define TERMINAL_INTERFACE_H
#include "movie_interface.h"

class TerminalInterface : public MovieInterface {
public:
    void run() override;

private:
    static void showAdminMenu();
    static void showUserMenu();
    void addMovie();
    void listMovies() const;
    void viewMovie() const;
    void deleteMovie();
    void clearMovies();
    static void editMovie(movie& m);
    static void editBaseProperties(movie& m);
};

#endif