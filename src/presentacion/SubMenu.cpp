// SubMenu.cpp
#include "SubMenu.h"
#include "GUI.h"

SubMenu::SubMenu() {
 initscr();
    start_color();
 init_pair(1,COLOR_GREEN, COLOR_BLACK);

}

SubMenu::~SubMenu() {
    endwin();
}

void SubMenu::clearScreen() {
    clear();
    refresh();
}


void SubMenu::tagsHtml() {
    int terminal_width = COLS; // Ancho de la terminal
    int terminal_height = LINES; // Altura de la terminal

    clearScreen();
    attron(COLOR_PAIR(1));
    mvprintw(0, 7, "+-------------------------------------------------------------------------------------------------+");
    mvprintw(terminal_height - 1, 7, "+-------------------------------------------------------------------------------------------------+");
    for (int i = 0; i < terminal_height; ++i) {
        mvprintw(i, 6, "|");
        mvprintw(i, terminal_width - 6, "|");
    }
    mvprintw(1, (terminal_width - 15) / 2, "tags del html"); // Centrar el título horizontalmente
    attroff(COLOR_PAIR(1));

    refresh();
    waitForInput();
}

void SubMenu::atributosHtml() {
    int menu_x = (COLS - 41) / 2; // Centrar el menú horizontalmente
    int menu_y = (LINES - 11) / 2;

    clearScreen();
    attron(COLOR_PAIR(1));
    mvprintw(menu_y - 11, menu_x - 1, "+----------------------------------------+");
    mvprintw(menu_y -5, menu_x - 1, "+----------------------------------------+");
    for (int i =-10; i < -5; ++i) {
        mvprintw(menu_y + i, menu_x - 1, "|");
        mvprintw(menu_y + i, menu_x + 40, "|");
    }
    mvprintw(menu_y - 10,menu_x +10 , " Atributos de un tag HTML"); // Centrar el título verticalmente
    attroff(COLOR_PAIR(1));

    refresh();
    waitForInput();
}

void SubMenu::enlacesHtml() {
    int menu_x = (COLS - 41) / 2; // Centrar el menú horizontalmente
    int menu_y = (LINES - 11) / 2;

    clearScreen();
    attron(COLOR_PAIR(1));
    mvprintw(menu_y - 11, menu_x - 1, "+----------------------------------------+");
    mvprintw(menu_y -5, menu_x - 1, "+----------------------------------------+");
    for (int i =-10; i < -5; ++i) {
        mvprintw(menu_y + i, menu_x - 1, "|");
        mvprintw(menu_y + i, menu_x + 40, "|");
    }
    mvprintw(menu_y -10 , menu_x +10,"enlaces de html"); // Centrar el título horizontalmente // Centrar el título verticalmente
    attroff(COLOR_PAIR(1));

    refresh();
    waitForInput();
}

void SubMenu::imagenesHtml() {
    int menu_x = (COLS - 41) / 2; // Centrar el menú horizontalmente
    int menu_y = (LINES - 11) / 2;

    clearScreen();
    attron(COLOR_PAIR(1));
    mvprintw(menu_y - 11, menu_x - 1, "+----------------------------------------+");
    mvprintw(menu_y -5, menu_x - 1, "+----------------------------------------+");
    for (int i =-10; i < -5; ++i) {
        mvprintw(menu_y + i, menu_x - 1, "|");
        mvprintw(menu_y + i, menu_x + 40, "|");
    }
    mvprintw(menu_y -10 , menu_x +10,"imagenes de html"); // Centrar el título horizontalmente // Centrar el título verticalmente
    attroff(COLOR_PAIR(1));

    refresh();
    waitForInput();
}