#ifndef COMMENT_H
#define COMMENT_H
#include <ctime>
#include <string>

class Comment {
private:
    std::string username;
    std::string movieTitle;
    std::string text;
    int rating;
    std::time_t timestamp;

public:
    Comment(const std::string& username, const std::string& movieTitle, const std::string& text, int rating = 0);
    

    std::string getUsername() const;
    std::string getMovieTitle() const;
    std::string getText() const;
    int getRating() const;
    std::time_t getTimestamp() const;
    std::string getFormattedTime() const;
    

    void setText(const std::string& newText);
    void setRating(int newRating);
    

    static bool isValidRating(int rating);
};

#endif