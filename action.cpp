#include "action.h"
#include <utility>

action::action()
    :movie("Unknown action", "Unknown director", "Unknown country", 0, 0, 0, 0, "No info"), ActionSubgenre(actionSubgenre::noInfo) {
    std::cout << "Default constructor was called for " << getTitle() << " of class action" << std::endl;
}

action::action(std::string t, std::string d, std::string c, int y, int b, int g, int rt, std:: string p, actionSubgenre subgenre)
    : movie(std::move(t), std::move(d), std::move(c), y, b, g, rt, std::move(p)), ActionSubgenre (subgenre) {
    std::cout << "Parameterized constructor was called for " << getTitle() << " of class action" << std::endl;
}

action::action(const action& other)
    : movie(other), ActionSubgenre(other.ActionSubgenre) {
    std::cout << "Copy constructor was called for " << getTitle() << " of class action" << std::endl;
}

action::action(action&& other) noexcept
    : movie(std::move(other)){
    std::cout << "Move constructor was called for " << getTitle() << " of class action" << std::endl;
}

action::~action() {
    std::cout << "The destructor was called for " << getTitle() << " of class action" << std::endl;
}


actionSubgenre action::getSubgenre() const noexcept{
    return ActionSubgenre;
}

void action::setSubgenre(actionSubgenre newSubgenre) {
        ActionSubgenre =newSubgenre;
}


std::string action::actionSubgenreToString(actionSubgenre subgenre) {
    switch (subgenre) {
        case actionSubgenre::noInfo: return "No info";
        case actionSubgenre::hybrid: return "Hybrid";
        case actionSubgenre::actionComedy: return "Action comedy";
        case actionSubgenre::martialArts: return "Martial arts";
        case actionSubgenre::wuxia: return "Wuxia";
        case actionSubgenre::kungFu: return "Kung-Fu";
        case actionSubgenre::americanStyle: return "American style";
        case actionSubgenre::heroicBloodshed: return "Heroic Bloodshed";
        default: return "Unknown";
    }
}


void action::displayDetails() const {
    std::cout << "Title: " << getTitle() << "\n"
    << "Subgenre: " << actionSubgenreToString(ActionSubgenre) << "\n"
    << "Director: " << getDirector() << "\n"
    << "Country: " << getCountry() << "\n"
    << "Year: " << getYear() << "\n"
    << "Budget: " << getBudget() << "\n"
    << "Gross: " << getGross() <<"\n"
    << "Running Time: " << getRunningTime() << " minutes\n"
    << "Plot: " << getPlot() << std::endl;
}
