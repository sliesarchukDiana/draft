#include "movie_service.h"

MovieService::MovieService(MovieRepository& repo, CommentManager& cm)
    : movieRepository(repo), commentManager(cm) {}

bool MovieService::addMovie(const movie& newMovie, const user* currentUser) const {
    if (!canModifyMovies(currentUser) || !validateMovie(newMovie)) {
        return false;
    }
    
    auto movieCopy = std::make_unique<movie>(newMovie);
    return movieRepository.addMovie(std::move(movieCopy));
}

bool MovieService::updateMovie(const std::string& title, const movie& updates, const user* currentUser) const {
    if (!canModifyMovies(currentUser)) {
        return false;
    }
    
    movie* existingMovie = movieRepository.findMovieByTitle(title);
    if (!existingMovie) {
        return false;
    }
    
    // Обновляем только заполненные поля
    if (!updates.getTitle().empty()) existingMovie->setTitle(updates.getTitle());
    if (updates.getGenre() != Genre::noInfo) existingMovie->setGenre(updates.getGenre());
    if (!updates.getDirector().empty()) existingMovie->setDirector(updates.getDirector());
    if (!updates.getCountry().empty()) existingMovie->setCountry(updates.getCountry());
    if (updates.getYear() > 0) existingMovie->setYear(updates.getYear());
    
    return true;
}

bool MovieService::deleteMovie(const std::string& title, const user* currentUser) const {
    if (!canModifyMovies(currentUser)) {
        return false;
    }
    return movieRepository.deleteMovie(title);
}

movie* MovieService::getMovieByTitle(const std::string& title) const {
    return movieRepository.findMovieByTitle(title);
}

std::vector<movie*> MovieService::searchMovies(const std::string& term) const {
    return movieRepository.searchMovies(term);
}

std::vector<movie*> MovieService::getAllMovies() const {
    return movieRepository.getAllMovies();
}

bool MovieService::addComment(const std::string& username, const std::string& movieTitle, 
                             const std::string& text, int rating) const {
    if (text.empty() || !movieRepository.movieExists(movieTitle)) {
        return false;
    }
    return commentManager.addComment(username, movieTitle, text, rating);
}

std::vector<Comment*> MovieService::getMovieComments(const std::string& movieTitle) const {
    return commentManager.getCommentsForMovie(movieTitle);
}

double MovieService::getMovieAverageRating(const std::string& movieTitle) const {
    return commentManager.getAverageRating(movieTitle);
}

bool MovieService::canModifyMovies(const user* currentUser) {
    return currentUser && currentUser->getHasAdministratorRights();
}

bool MovieService::validateMovie(const movie& m) const {
    return !m.getTitle().empty() && 
           m.getYear() >= 1888 && 
           m.getYear() <= 2025 &&
           !movieRepository.movieExists(m.getTitle());
}