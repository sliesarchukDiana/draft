#include "comment_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

CommentManager::CommentManager() {
    loadCommentsFromFile();
}

void CommentManager::loadCommentsFromFile() {
    std::ifstream file(commentsFile);
    if (!file.is_open()) {
        std::cout << "Comments file not found. Creating new one.\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string username, movieTitle, text, ratingStr, timestampStr;
        
        if (std::getline(iss, username, '|') &&
            std::getline(iss, movieTitle, '|') &&
            std::getline(iss, text, '|') &&
            std::getline(iss, ratingStr, '|') &&
            std::getline(iss, timestampStr)) {
            
            // Заменяем специальные символы в тексте
            size_t pos = 0;
            while ((pos = text.find("\\n")) != std::string::npos) {
                text.replace(pos, 2, "\n");
            }
            
            int rating = std::stoi(ratingStr);
            
            auto comment = std::make_unique<Comment>(username, movieTitle, text, rating);
            commentsByMovie[movieTitle].push_back(std::move(comment));
        }
    }
    file.close();
}

void CommentManager::saveCommentsToFile() const {
    std::ofstream file(commentsFile);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot save comments to file!\n";
        return;
    }

    for (const auto& pair : commentsByMovie) {
        for (const auto& comment : pair.second) {
            std::string text = comment->getText();
            // Заменяем переносы строк на специальные символы для сохранения
            size_t pos = 0;
            while ((pos = text.find('\n')) != std::string::npos) {
                text.replace(pos, 1, "\\n");
            }
            
            file << comment->getUsername() << "|"
                 << comment->getMovieTitle() << "|"
                 << text << "|"
                 << comment->getRating() << "|"
                 << comment->getTimestamp() << "\n";
        }
    }
    file.close();
}

bool CommentManager::addComment(const std::string& username, const std::string& movieTitle, 
                               const std::string& text, int rating) {
    if (text.empty()) {
        std::cout << "Error: Comment text cannot be empty!\n";
        return false;
    }
    
    if (rating != 0 && !Comment::isValidRating(rating)) {
        std::cout << "Error: Rating must be between 1 and 10!\n";
        return false;
    }
    
    commentsByMovie[movieTitle].push_back(
        std::make_unique<Comment>(username, movieTitle, text, rating));
    saveCommentsToFile();
    return true;
}

bool CommentManager::removeComment(const std::string& username, const std::string& movieTitle) {
    auto it = commentsByMovie.find(movieTitle);
    if (it != commentsByMovie.end()) {
        auto& comments = it->second;
        auto newEnd = std::remove_if(comments.begin(), comments.end(),
            [&username](const std::unique_ptr<Comment>& comment) {
                return comment->getUsername() == username;
            });
        
        if (newEnd != comments.end()) {
            comments.erase(newEnd, comments.end());
            saveCommentsToFile();
            return true;
        }
    }
    return false;
}

std::vector<Comment*> CommentManager::getCommentsForMovie(const std::string& movieTitle) const {
    std::vector<Comment*> result;
    auto it = commentsByMovie.find(movieTitle);
    if (it != commentsByMovie.end()) {
        for (const auto& comment : it->second) {
            result.push_back(comment.get());
        }
    }
    return result;
}

std::vector<Comment*> CommentManager::getCommentsByUser(const std::string& username) const {
    std::vector<Comment*> result;
    for (const auto& pair : commentsByMovie) {
        for (const auto& comment : pair.second) {
            if (comment->getUsername() == username) {
                result.push_back(comment.get());
            }
        }
    }
    return result;
}

double CommentManager::getAverageRating(const std::string& movieTitle) const {
    auto comments = getCommentsForMovie(movieTitle);
    if (comments.empty()) return 0.0;
    
    int sum = 0;
    int count = 0;
    for (const auto& comment : comments) {
        if (comment->getRating() > 0) {
            sum += comment->getRating();
            count++;
        }
    }
    
    return count > 0 ? static_cast<double>(sum) / count : 0.0;
}

int CommentManager::getRatingCount(const std::string& movieTitle) const {
    auto comments = getCommentsForMovie(movieTitle);
    int count = 0;
    for (const auto& comment : comments) {
        if (comment->getRating() > 0) count++;
    }
    return count;
}

void CommentManager::displayCommentsForMovie(const std::string& movieTitle) const {
    auto comments = getCommentsForMovie(movieTitle);
    if (comments.empty()) {
        std::cout << "No comments for this movie yet.\n";
        return;
    }
    
    std::cout << "=== Comments for \"" << movieTitle << "\" ===\n";
    for (size_t i = 0; i < comments.size(); ++i) {
        const auto& comment = comments[i];
        std::cout << i + 1 << ". " << comment->getUsername() 
                  << " (" << comment->getFormattedTime() << ")\n";
        
        if (comment->getRating() > 0) {
            std::cout << "   Rating: " << comment->getRating() << "/10\n";
        }
        
        std::cout << "   " << comment->getText() << "\n\n";
    }
    
    double avgRating = getAverageRating(movieTitle);
    if (avgRating > 0) {
        std::cout << "Average rating: " << avgRating << "/10 (" 
                  << getRatingCount(movieTitle) << " ratings)\n";
    }
}