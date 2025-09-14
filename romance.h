#ifndef ROMANCE_H
#define ROMANCE_H
#include "movie.h"

class romance: public movie {
    private:
        bool happyEnding{};

    public:
        romance();
        romance(std::string title, std::string director, std::string country, int year, int budget, int gross, int runningTime, std::string plot, bool happyEnding);
        romance(const romance& other);
        romance(romance&& other) noexcept;
        ~romance() override;

        static std::string happyEndingToMessage(bool ending);
        bool getHappyEnding() const;

        void setHappyEnding(bool newHappyEnding);

        void displayDetails() const override;
    };
#endif //ROMANCE_H
