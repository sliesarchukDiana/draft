#ifndef ACTION_H
#define ACTION_H
#include "movie.h"
#include <string>

enum class actionSubgenre {
    noInfo,
    hybrid,
    actionComedy,
    martialArts,
    wuxia,
    kungFu,
    americanStyle,
    heroicBloodshed
};

class action final : public movie {
public:
    action();
    action(std::string title, std::string director, std::string country, int year, int budget, int gross, int runningTime, std::string plot, actionSubgenre subgenre);
    action(const action& other);
    action(action&& other) noexcept;
    ~action() override;

    actionSubgenre getSubgenre() const noexcept;
    void setSubgenre(actionSubgenre subgenre);
    void displayDetails() const override;
    static std::string actionSubgenreToString(actionSubgenre subgenre);

    private:
    actionSubgenre ActionSubgenre;
};

#endif // ACTION_H