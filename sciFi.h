#ifndef SCIFI_H
#define SCIFI_H
#include "movie.h"
#include <iosfwd>

enum class TimePeriod {
    NoInfo,
    NearFuture,
    Dystopian,
    Cyberpunk,
    SpaceAge,
    AlternateHistory
};

class sciFy : public movie {
public:
    sciFy();
    sciFy(std::string title, std::string director, std::string country, int year, int budget, int gross, int runningTime, std::string plot, TimePeriod period);
    sciFy(const sciFy& other);
    sciFy(sciFy&& other) noexcept;
    ~sciFy() override;

    TimePeriod getTimePeriod() const noexcept;
    void setTimePeriod(TimePeriod period);

    void displayDetails() const override;

    static std::string timePeriodToString(TimePeriod period);

private:
    TimePeriod timePeriod;
};

#endif // SCIFI_H