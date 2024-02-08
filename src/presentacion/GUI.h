#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>
#include "../negocio/HTMLParser.h"

inline void waitForInput() {
    std::cin.ignore();
    std::cin.get(); 
}

class GUI {
private:
    HTMLParser parser;

public:
    GUI(HTMLParser parser);  // Constructor
    ~GUI(); // Destructor
    void showMenu();
    void clearScreen();

private:
    void handleOption(int option);
};

#endif // GUI_H


