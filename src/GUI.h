#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
const std::string SO = "WIN";
#elif __linux__
const std::string SO = "UNIX";
#endif

inline void clearScreen() {
    if (SO == "WIN") {
        system("cls");
    } else if (SO == "UNIX") {
        system("clear");
    }
}

inline void waitForInput() {
    std::cin.ignore();
    std::cin.get(); 
}

class GUI {
public:
    GUI();  // Constructor
    ~GUI(); // Destructor
    void showMenu();

private:
    void handleOption(int option);
};

#endif // GUI_H


