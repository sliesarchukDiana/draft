#include "comment.h"
#include <iomanip>
#include <sstream>
#include <chrono>

Comment::Comment(const std::string& username, const std::string& movieTitle, const std::string& text, int rating)
    : username(username), movieTitle(movieTitle), text(text), rating(rating) {
    timestamp = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now());
}

std::string Comment::getUsername() const { return username; }
std::string Comment::getMovieTitle() const { return movieTitle; }
std::string Comment::getText() const { return text; }
int Comment::getRating() const { return rating; }
std::time_t Comment::getTimestamp() const { return timestamp; }

std::string Comment::getFormattedTime() const {
    std::tm* timeinfo = std::localtime(&timestamp);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Comment::setText(const std::string& newText) {
    text = newText;
}

void Comment::setRating(int newRating) {
    if (isValidRating(newRating)) {
        rating = newRating;
    }
}

bool Comment::isValidRating(int rating) {
    return rating >= 1 && rating <= 10;
}