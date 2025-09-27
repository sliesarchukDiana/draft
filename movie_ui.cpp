#include "movie_ui.h"
#include "user.h"
#include <iostream>
#include <limits>

MovieUI::MovieUI(MovieService& service) : movieService(service) {}

int MovieUI::getInt(const std::string& prompt, int min, int max) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value >= min && value <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return value;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
    }
}

std::string MovieUI::getString(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

bool MovieUI::getYesNo(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin, input);
        if (input == "y" || input == "Y") return true;
        if (input == "n" || input == "N") return false;
        std::cout << "Please enter 'y' or 'n'.\n";
    }
}

movie MovieUI::createMovieFromInput() const {
    std::string title = getString("Enter movie title: ");

    if (movieService.getMovieByTitle(title)) {
        std::cout << "Movie with this title already exists!\n";
        return {};
    }

    std::string genreStr = getString("Enter genre: ");
    Genre genre = stringToGenre(genreStr);
    std::string director = getString("Enter director: ");
    std::string country = getString("Enter country: ");
    int year = getInt("Enter year: ", 1888, 2025);
    int budget = getInt("Enter budget: ", 0, 1000000000);
    int gross = getInt("Enter gross: ", 0, 1000000000);
    int runningTime = getInt("Enter running time (minutes): ", 1, 1000);
    std::string plot = getString("Enter plot: ");

    return {title, genre, director, country, year, budget, gross, runningTime, plot};
}

void MovieUI::displayAllMovies() const {
    auto movies = movieService.getAllMovies();
    if (movies.empty()) {
        std::cout << "No movies available.\n";
        return;
    }

    std::cout << "=== All Movies ===\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << i + 1 << ". " << movies[i]->getTitle()
                  << " (" << movies[i]->getYear() << ")\n";
    }
}

void MovieUI::displayMovieDetails(const std::string& title) const {
    movie* movie = movieService.getMovieByTitle(title);
    if (!movie) {
        std::cout << "Movie not found!\n";
        return;
    }

    std::cout << *movie;
    double avgRating = movieService.getMovieAverageRating(title);
    if (avgRating > 0) {
        std::cout << "Average rating: " << avgRating << "/10\n";
    }
}

void MovieUI::addMovieUI(user* currentUser) const {
    if (!currentUser || !currentUser->getHasAdministratorRights()) {
        std::cout << "Administrator rights required!\n";
        return;
    }

    movie newMovie = createMovieFromInput();
    if (newMovie.getTitle().empty()) {
        return;
    }

    if (movieService.addMovie(newMovie, currentUser)) {
        std::cout << "Movie added successfully!\n";
    } else {
        std::cout << "Failed to add movie.\n";
    }
}

void MovieUI::searchAndDisplayMovies() const {
    std::string searchTerm = getString("Enter search term (title, director, or genre): ");
    auto results = movieService.searchMovies(searchTerm);

    if (results.empty()) {
        std::cout << "No movies found.\n";
        return;
    }

    std::cout << "=== Search Results ===\n";
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << i + 1 << ". " << results[i]->getTitle()
                  << " (" << results[i]->getYear() << ")\n";
    }
}

void MovieUI::addCommentUI(user* currentUser) const {
    if (!currentUser) {
        std::cout << "You need to be logged in to comment!\n";
        return;
    }

    std::string movieTitle = getString("Enter movie title: ");
    movie* movie = movieService.getMovieByTitle(movieTitle);
    if (!movie) {
        std::cout << "Movie not found!\n";
        return;
    }

    std::cout << "Enter your comment (press Enter twice to finish):\n";
    std::string commentText;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        commentText += line + "\n";
    }

    if (!commentText.empty()) {
        commentText.pop_back();
    }

    int rating = 0;
    if (getYesNo("Would you like to add a rating?")) {
        rating = getInt("Enter rating (1-10): ", 1, 10);
    }

    if (movieService.addComment(currentUser->getUsername(), movieTitle, commentText, rating)) {
        std::cout << "Comment added successfully!\n";
    } else {
        std::cout << "Failed to add comment.\n";
    }
}

void MovieUI::editMovieUI(user* currentUser) const {
    if (!currentUser || !currentUser->getHasAdministratorRights()) {
        std::cout << "Administrator rights required!\n";
        return;
    }

    std::string title = getString("Enter movie title to edit: ");
    movie* movieToEdit = movieService.getMovieByTitle(title);
    if (!movieToEdit) {
        std::cout << "Movie not found!\n";
        return;
    }

    std::cout << "Editing movie: " << title << "\n";
    std::cout << "Leave field empty to keep current value.\n";

    movie updates;

    std::string newTitle = getString("New title [" + movieToEdit->getTitle() + "]: ");
    if (!newTitle.empty()) updates.setTitle(newTitle);

    std::string newGenre = getString("New genre [" + fromEnumToString(movieToEdit->getGenre()) + "]: ");
    if (!newGenre.empty()) updates.setGenre(stringToGenre(newGenre));

    std::string newDirector = getString("New director [" + movieToEdit->getDirector() + "]: ");
    if (!newDirector.empty()) updates.setDirector(newDirector);

    std::string newCountry = getString("New country [" + movieToEdit->getCountry() + "]: ");
    if (!newCountry.empty()) updates.setCountry(newCountry);

    std::string yearStr = getString("New year [" + std::to_string(movieToEdit->getYear()) + "]: ");
    if (!yearStr.empty()) updates.setYear(std::stoi(yearStr));

    if (movieService.updateMovie(title, updates, currentUser)) {
        std::cout << "Movie updated successfully!\n";
    } else {
        std::cout << "Failed to update movie.\n";
    }
}

void MovieUI::deleteMovieUI(user* currentUser) const {
    if (!currentUser || !currentUser->getHasAdministratorRights()) {
        std::cout << "Administrator rights required!\n";
        return;
    }

    std::string title = getString("Enter movie title to delete: ");
    if (movieService.deleteMovie(title, currentUser)) {
        std::cout << "Movie deleted successfully!\n";
    } else {
        std::cout << "Failed to delete movie.\n";
    }
}

void MovieUI::viewWatchlist(user* currentUser) {
    if (!currentUser) {
        std::cout << "You need to be logged in to view your watchlist!\n";
        return;
    }

    auto watchlist = currentUser->getWatchlist();
    if (watchlist.empty()) {
        std::cout << "Your watchlist is empty.\n";
        return;
    }

    std::cout << "=== Your Watchlist ===\n";
    for (size_t i = 0; i < watchlist.size(); ++i) {
        std::cout << i + 1 << ". " << watchlist[i].getTitle()
                  << " (" << watchlist[i].getYear() << ")\n";
    }
}

void MovieUI::addToWatchlist(user* currentUser) const {
    if (!currentUser) {
        std::cout << "You need to be logged in to add to watchlist!\n";
        return;
    }

    std::string title = getString("Enter movie title to add to watchlist: ");
    movie* movieObj = movieService.getMovieByTitle(title);

    if (movieObj) {
        // Need to cast away const to modify the user's watchlist
        currentUser->addToWatchlist(*movieObj);
        std::cout << "Movie added to watchlist successfully!\n";
    } else {
        std::cout << "Movie not found!\n";
    }
}

void MovieUI::removeFromWatchlist(user* currentUser) {
    if (!currentUser) {
        std::cout << "You need to be logged in to remove from watchlist!\n";
        return;
    }

    std::string title = getString("Enter movie title to remove from watchlist: ");
    // Need to cast away const to modify the user's watchlist
    currentUser->removeFromWatchlist(title);
    std::cout << "Movie removed from watchlist successfully!\n";
}

void MovieUI::displayMainMenu(user* currentUser) const {
    while (true) {
        std::cout << "\n=== Movie Database ===";
        if (currentUser) {
            std::cout << " | Logged in as: " << currentUser->getUsername();
            if (currentUser->getHasAdministratorRights()) {
                std::cout << " (Admin)";
            }
        }
        std::cout << "\n";

        std::cout << "1. View all movies\n";
        std::cout << "2. Search movies\n";
        std::cout << "3. View movie details\n";
        std::cout << "4. Add comment\n";

        if (currentUser) {
            std::cout << "5. View my watchlist\n";
            std::cout << "6. Add to watchlist\n";
            std::cout << "7. Remove from watchlist\n";

            if (currentUser->getHasAdministratorRights()) {
                std::cout << "8. Add movie (Admin)\n";
                std::cout << "9. Edit movie (Admin)\n";
                std::cout << "10. Delete movie (Admin)\n";
            }
        } else {
            std::cout << "5. Login\n";
            std::cout << "6. Register\n";
        }

        std::cout << "0. Exit\n";

        int maxOption = currentUser ? (currentUser->getHasAdministratorRights() ? 10 : 7) : 6;
        int choice = getInt("Choose option: ", 0, maxOption);

        switch (choice) {
            case 0:
                std::cout << "Goodbye!\n";
                return;
            case 1:
                displayAllMovies();
                break;
            case 2:
                searchAndDisplayMovies();
                break;
            case 3: {
                std::string title = getString("Enter movie title: ");
                displayMovieDetails(title);
                break;
            }
            case 4:
                addCommentUI(currentUser);
                break;
            case 5:
                if (currentUser) {
                    viewWatchlist(currentUser);
                } else {
                    std::cout << "Please login from main application menu.\n";
                }
                break;
            case 6:
                if (currentUser) {
                    addToWatchlist(currentUser);
                } else {
                    std::cout << "Please register from main application menu.\n";
                }
                break;
            case 7:
                if (currentUser) {
                    removeFromWatchlist(currentUser);
                }
                break;
            case 8:
                if (currentUser && currentUser->getHasAdministratorRights()) {
                    addMovieUI(currentUser);
                }
                break;
            case 9:
                if (currentUser && currentUser->getHasAdministratorRights()) {
                    editMovieUI(currentUser);
                }
                break;
            case 10:
                if (currentUser && currentUser->getHasAdministratorRights()) {
                    deleteMovieUI(currentUser);
                }
                break;
            default:
                std::cout << "Invalid choice!\n";
        }
    }
}