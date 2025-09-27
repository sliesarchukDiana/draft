#ifndef COMMENT_MANAGER_H
#define COMMENT_MANAGER_H

#include "comment.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>

class CommentManager {
private:
    std::unordered_map<std::string, std::vector<std::unique_ptr<Comment>>> commentsByMovie;
    const std::string commentsFile = "comments.txt";

    void loadCommentsFromFile();
    void saveCommentsToFile() const;

public:
    CommentManager();
    
    bool addComment(const std::string& username, const std::string& movieTitle, 
                   const std::string& text, int rating = 0);
    bool removeComment(const std::string& username, const std::string& movieTitle);
    std::vector<Comment*> getCommentsForMovie(const std::string& movieTitle) const;
    std::vector<Comment*> getCommentsByUser(const std::string& username) const;
    double getAverageRating(const std::string& movieTitle) const;
    int getRatingCount(const std::string& movieTitle) const;
    
    void displayCommentsForMovie(const std::string& movieTitle) const;
};

#endif