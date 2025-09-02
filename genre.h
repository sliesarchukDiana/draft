#ifndef DRAFT_GENRE_H
#define DRAFT_GENRE_H
#include <string>

class genre {
private:
    std::string name;
    std::string description;
public:
    genre();
    genre(std::string name, std::string description);
    genre (const genre& other);
    genre& operator=(const genre& other);
    genre(genre&& other) noexcept;
    ~genre();

    std::string getName() ;
    std::string getDescription();

    void setName(std::string newName);
    void setDescription(std::string description);




};


#endif //DRAFT_GENRE_H