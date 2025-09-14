#ifndef MOVIE_H
#define MOVIE_H
#include <string>
#include <iostream>
class movie {
private:
    std::string title;
    std::string director;
    std::string plot;
    int runningTime;
    int budget;
    static int count;
public:
    movie();
    movie(std::string title, std::string director, std::string plot, int runningTime, int budget);
    movie(const movie& other); //copy//
    movie(movie&& other) noexcept; //move//
    virtual ~movie();

    std::string getTitle() const;
    std::string getDirector() const;
    std::string getPlot() const;
    int getRunningTime() const;
    int getBudget() const;

    static int getObjectCount();

    void setTitle(const std::string& newTitle);
    void setDirector(const std::string& newDirector);
    void setPlot(const std::string& newPlot);
    void setRunningTime(int newRunningTime);
    void setBudget(int newBudget);

    friend std::ostream& operator<<(std::ostream& os, const movie& t);
    friend std::istream& operator>>(std::istream& is, movie& t);
    friend int operator+(const movie& lhs, const movie& rhs);

    virtual void displayDetails() const = 0;

    movie& operator=(const movie& other); //copy assignment operator//

    //static binding//
    void printBasicInfo() const {
        std::cout << "[Static Binding] Title: " << title
                  << " | Director: " << director << "\n";
    }
};

#endif // MOVIE_H