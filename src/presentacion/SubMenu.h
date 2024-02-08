// SubMenu.h
#ifndef SubMenu_h
#define SubMenu_h

#include <iostream>
#include <ncurses.h>



class SubMenu {

private:
    void clearScreen();

public:
    SubMenu();  // constructor
    ~SubMenu(); // destructor
    void tagsHtml();
    void atributosHtml();
    void enlacesHtml();
    void imagenesHtml();


};

#endif





