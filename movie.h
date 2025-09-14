#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>
class movie {
private:
    static int count;
    std::string title;
    std::string director;
    std::string country;
    int year;
    int budget;
    int gross;
    int runningTime;
    std::string plot;
public:
    movie();
    movie(std::string title, std::string director, std::string country, int year, int budget, int gross, int runningTime, std::string plot);
    movie(const movie& other); //copy//
    movie(movie&& other) noexcept; //move//
    virtual ~movie();

    std::string getTitle() const;
    std::string getDirector() const;
    std::string getCountry() const;
    int getYear() const;
    int getBudget() const;
    int getGross() const;
    int getRunningTime() const;
    std::string getPlot() const;

    static int getObjectCount();

    void setTitle(const std::string& newTitle);
    void setDirector(const std::string& newDirector);
    void setCountry(const std::string& newCountry);
    void setYear(int newYear);
    void setBudget(int newBudget);
    void setGross(int newGross);
    void setRunningTime(int newRunningTime);
    void setPlot(const std::string& newPlot);

    friend std::ostream& operator<<(std::ostream& os, const movie& t);
    friend std::istream& operator>>(std::istream& is, movie& t);

    virtual void displayDetails() const = 0;

    movie& operator=(const movie& other);
};

#endif // MOVIE_H