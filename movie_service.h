#ifndef MOVIE_SERVICE_H
#define MOVIE_SERVICE_H

#include "movie_repository.h"
#include "comment_manager.h"
#include "user.h"
#include <memory>

class MovieService {
private:
    MovieRepository& movieRepository;
    CommentManager& commentManager;

public:
    MovieService(MovieRepository& repo, CommentManager& cm);
    ~MovieService() = default;

    // Управление фильмами
    bool addMovie(const movie& newMovie, const user* currentUser) const;
    bool updateMovie(const std::string& title, const movie& updates, const user* currentUser) const;
    bool deleteMovie(const std::string& title, const user* currentUser) const;
    
    // Поиск и получение
    movie* getMovieByTitle(const std::string& title) const;
    std::vector<movie*> searchMovies(const std::string& term) const;
    std::vector<movie*> getAllMovies() const;
    
    // Комментарии и рейтинги
    bool addComment(const std::string& username, const std::string& movieTitle, 
                   const std::string& text, int rating = 0) const;
    std::vector<Comment*> getMovieComments(const std::string& movieTitle) const;
    double getMovieAverageRating(const std::string& movieTitle) const;
    
    // Валидация прав доступа
    static bool canModifyMovies(const user* currentUser) ;

private:
    bool validateMovie(const movie& m) const;
};

#endif