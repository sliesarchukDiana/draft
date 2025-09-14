#ifndef SCIFY_H
#define SCIFY_H
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
    sciFy(std::string title, std::string director, std::string plot, int runningTime, int budget, TimePeriod period);
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

#endif // SCIFY_H