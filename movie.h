#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>

enum class Genre {
    noInfo,
    drama,
    romance,
    thriller,
    scienceFiction,
    crime,
    horror,
    action,
    western,
    mystery,
    historical,
    comedy,
    fantasy,
    animation,
    adventure,
    documentary
};
Genre stringToGenre(const std::string& genreStr);


class movie {
private:
    static int count;
    std::string title;
    Genre genre;
    std::string director;
    std::string country;
    int year;
    int budget;
    int gross;
    int runningTime;
    std::string plot;
public:
    movie();
    movie(std::string title, Genre genre, std::string director, std::string country, int year, int budget, int gross, int runningTime, std::string plot);
    movie(const movie& other); //copy//
    movie(movie&& other) noexcept; //move//
    ~movie();

    std::string getTitle() const;
    Genre getGenre() const;
    std::string getDirector() const;
    std::string getCountry() const;
    int getYear() const;
    int getBudget() const;
    int getGross() const;
    int getRunningTime() const;
    std::string getPlot() const;

    static int getObjectCount();

    void setTitle(const std::string& newTitle);
    void setGenre (Genre newGenre);
    void setDirector(const std::string& newDirector);
    void setCountry(const std::string& newCountry);
    void setYear(int newYear);
    void setBudget(int newBudget);
    void setGross(int newGross);
    void setRunningTime(int newRunningTime);
    void setPlot(const std::string& newPlot);

    friend std::ostream& operator<<(std::ostream& os, const movie& t);
    friend std::istream& operator>>(std::istream& is, movie& t);
    movie& operator=(const movie& other);

    movie &operator=(movie &&other) noexcept;
};

#endif // MOVIE_H