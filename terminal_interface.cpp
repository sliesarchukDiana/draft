#include "terminal_interface.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <fstream>
#include "action.h"
#include "sciFy.h"
#include "romance.h"
#include "thriller.h"

using namespace std;

int MovieInterface::getInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
            cout << "Please enter between " << min << " and " << max << endl;
        } else {
            cout << "Invalid number. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string MovieInterface::getString(const string& prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        if (!input.empty()) return input;
        cout << "Input cannot be empty." << endl;
    }
}

bool MovieInterface::getYesNo(const string& prompt) {
    char input;
    while (true) {
        cout << prompt;
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input = static_cast<char>(tolower(static_cast<unsigned char>(input)));
        if (input == 'y') return true;
        if (input == 'n') return false;
        cout << "Please enter 'y' or 'n'." << endl;
    }
}

void MovieInterface::loadMovies() {
    ifstream file("movies.txt");
    if (!file.is_open()) return;

    string type, title, director, plot;
    int runtime, budget, explosions;
    bool happy, isChildFriendly;

    while (getline(file, type)) {
        getline(file, title);
        getline(file, director);
        getline(file, plot);
        file >> runtime >> budget;
        file.ignore();

        if (type == "ACTION") {
            file >> explosions;
            file.ignore();
            movies.push_back(make_unique<action>(title, director, plot, runtime, budget, explosions));
        }
        else if (type == "SCIFI") {
            int p;
            file >> p;
            file.ignore();
            auto period = static_cast<TimePeriod>(p);
            movies.push_back(make_unique<sciFy>(title, director, plot, runtime, budget, period));
        }
        else if (type == "ROMANCE") {
            file >> happy;
            file.ignore();
            movies.push_back(make_unique<romance>(title, director, plot, runtime, budget, happy));
        }
        else if (type == "THRILLER") {
            file >> isChildFriendly;
            file.ignore();
            movies.push_back(make_unique<thriller>(title, director, plot, runtime, budget, isChildFriendly));
        }
    }
    file.close();
}

void MovieInterface::saveMovies() const {
    ofstream file("movies.txt");
    if (!file.is_open()) throw runtime_error("Could not save movies to file");

    for (const auto& m : movies) {
        if (dynamic_cast<action*>(m.get())) {
            auto* a = dynamic_cast<action*>(m.get());
            file << "ACTION\n" << a->getTitle() << "\n" << a->getDirector() << "\n" << a->getPlot() << "\n" << a->getRunningTime() << " " << a->getBudget() << "\n" << a->getExplosions() << "\n";
        }
        else if (dynamic_cast<sciFy*>(m.get())) {
            auto* s = dynamic_cast<sciFy*>(m.get());
            file << "SCIFI\n" << s->getTitle() << "\n" << s->getDirector() << "\n" << s->getPlot() << "\n" << s->getRunningTime() << " " << s->getBudget() << "\n" << static_cast<int>(s->getTimePeriod()) << "\n";
        }
        else if (dynamic_cast<romance*>(m.get())) {
            auto* r = dynamic_cast<romance*>(m.get());
            file << "ROMANCE\n" << r->getTitle() << "\n" << r->getDirector() << "\n" << r->getPlot() << "\n" << r->getRunningTime() << " " << r->getBudget() << "\n" << r->getHappyEnding() << "\n";
        }
        else if (dynamic_cast<thriller*>(m.get())) {
            auto* t = dynamic_cast<thriller*>(m.get());
            file << "THRILLER\n" << t->getTitle() << "\n" << t->getDirector() << "\n" << t->getPlot() << "\n" << t->getRunningTime() << " " << t->getBudget() << "\n" << t->getIsChildFriendly() << "\n";
        }
    }
    file.close();
}

void TerminalInterface::run() {
    loadMovies();

    cout << "1. Admin\n2. User\n";
    int role = getInt("Select role: ", 1, 2);

    if (role == 1) {
        string password = getString("Enter admin password: ");
        if (password != "admin123") {
            cout << "Wrong password. Switching to user mode.\n";
            role = 2;
        }
    }

    while (true) {
        if (role == 1) showAdminMenu();
        else showUserMenu();

        int choice = getInt("Enter choice: ", 1, role == 1 ? 7 : 3);

        try {
            switch (choice) {
                case 1:
                    if (role == 1) addMovie();
                    else listMovies();
                    break;
                case 2:
                    if (role == 1) listMovies();
                    else viewMovie();
                    break;
                case 3:
                    if (role == 1) viewMovie();
                    else return;
                    break;
                case 4: deleteMovie(); break;
                case 5: clearMovies(); break;
                case 6: {
                    if (!movies.empty()) {
                        listMovies();
                        int editChoice = getInt("Select movie to edit: ", 1, static_cast<int>(movies.size()));
                        editMovie(*movies[editChoice-1]);
                    }
                    break;
                }
                case 7:
                    saveMovies();
                    return;
                default: break;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
}

void TerminalInterface::showAdminMenu() {
    cout << "\n==== Admin Menu ====\n"
         << "1. Add Movie\n"
         << "2. List Movies\n"
         << "3. View Movie Details\n"
         << "4. Delete Movie\n"
         << "5. Clear All Movies\n"
         << "6. Edit Movie\n"
         << "7. Exit\n";
}

void TerminalInterface::showUserMenu() {
    cout << "\n==== User Menu ====\n"
         << "1. List Movies\n"
         << "2. View Movie Details\n"
         << "3. Exit\n";
}
void TerminalInterface::addMovie() {
    cout << "\n=== Add New Movie ===\n";
    cout << "1. Action\n2. Sci-Fi\n3. Romance\n4. Thriller\n";
    int type = getInt("Select type: ", 1, 4);

    string title = getString("Title: ");
    string director = getString("Director: ");
    string plot = getString("Plot: ");
    int runtime = getInt("Runtime (minutes): ", 1, 300);
    int budget = getInt("Budget: ", 0, INT_MAX);

    switch (type) {
        case 1: {
            int explosions = getInt("Explosion count: ", 0, 1000);
            movies.push_back(make_unique<action>(title, director, plot, runtime, budget, explosions));
            break;
        }
        case 2: {
            cout << "1. No Info\n2. Near Future\n3. Dystopian\n" << "4. Cyberpunk\n5. Space Age\n6. Alternate History\n";
            TimePeriod period = static_cast<TimePeriod>(getInt("Time period: ", 1, 6) - 1);
            movies.push_back(make_unique<sciFy>(title, director, plot, runtime, budget, period));
            break;
        }
        case 3: {
            bool happy = getYesNo("Happy ending? (y/n): ");
            movies.push_back(make_unique<romance>(title, director, plot, runtime, budget, happy));
            break;
        }
        case 4: {
            bool isChildFriendly = getYesNo("Is the movie safe for younger audience? (y/n): ");
            movies.push_back(make_unique<thriller>(title, director, plot, runtime, budget, isChildFriendly));
            break;
        }
        default:
            cout << "Invalid movie type." << endl;
            return;
    }
    cout << "Movie added successfully!\n";
}

void TerminalInterface::listMovies() const {
    if (movies.empty()) {
        cout << "No movies available.\n";
        return;
    }

    cout << "\n=== Movie List ===\n";
    for (size_t i = 0; i < movies.size(); i++) {
        cout << static_cast<int>(i+1) << ". " << movies[i]->getTitle() << endl;
    }
}

void TerminalInterface::viewMovie() const {
    listMovies();
    if (movies.empty()) return;

    int choice = getInt("Select movie to view: ", 1, static_cast<int>(movies.size()));
    const movie& movieRef = *movies[choice - 1]; // Base class reference
    // Static binding
    movieRef.printBasicInfo();
    // Dynamic binding
    movieRef.displayDetails();
}

void TerminalInterface::deleteMovie() {
    listMovies();
    if (movies.empty()) return;

    int choice = getInt("Select movie to delete: ", 1, static_cast<int>(movies.size()));
    movies.erase(movies.begin() + choice - 1);
    cout << "Movie deleted.\n";
}

void TerminalInterface::clearMovies() {
    if (movies.empty()) {
        cout << "No movies to clear.\n";
        return;
    }

    if (getYesNo("Clear ALL movies? (y/n): ")) {
        movies.clear();
        cout << "All movies cleared.\n";
    }
}


void TerminalInterface::editMovie(movie& m) {
    cout << "\n=== Editing Movie ===\n";
    editBaseProperties(m);
    cout << "Movie updated successfully!\n";
}

void TerminalInterface::editBaseProperties(movie& m) {
    cout << "Current title: " << m.getTitle() << endl;
    string newTitle = getString("New title (enter to keep current): ");
    if (!newTitle.empty()) m.setTitle(newTitle);

    cout << "Current director: " << m.getDirector() << endl;
    string newDirector = getString("New director (enter to keep current): ");
    if (!newDirector.empty()) m.setDirector(newDirector);

    cout << "Current plot: " << m.getPlot() << endl;
    string newPlot = getString("New plot (enter to keep current): ");
    if (!newPlot.empty()) m.setPlot(newPlot);

    cout << "Current runtime: " << m.getRunningTime() << " minutes\n";
    int newRuntime = getInt("New runtime (0 to keep current): ", 0, 1000);
    if (newRuntime > 0) m.setRunningTime(newRuntime);

    cout << "Current budget: $" << m.getBudget() << endl;
    int newBudget = getInt("New budget (0 to keep current): ", 0, INT_MAX);
    if (newBudget > 0) m.setBudget(newBudget);
}