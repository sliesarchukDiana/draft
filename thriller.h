#ifndef THRILLER_H
#define THRILLER_H
#include <string>
#include "movie.h"

class thriller: public movie {
private:
    bool isChildFriendly{};
public:
    thriller();
    thriller(std::string title, std::string director, std::string plot, int runningTime, int budget, bool isChildFriendly);
    thriller(const thriller& other); //copy constructor//
    thriller(thriller&& other) noexcept; //move constructor//
    ~thriller() override;

    static std::string isChildFriendlyToMessage(bool ending);

    bool getIsChildFriendly() const;
    void setIsChildFriendly(bool newIsChildFriendly);
    void displayDetails() const override;
};
#endif // THRILLER_H