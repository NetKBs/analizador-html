#include "GUI.h"
#include "SubMenu.h"
#include <ncurses.h>
GUI::GUI(HTMLParser parser) {
    this->parser = parser;
    initscr();         // Inicializar ncurses
    start_color();     // Habilitar el uso de colores
    keypad(stdscr, TRUE); // Habilitar el teclado numérico
    init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Definir un par de colores personalizados
    init_pair(2, COLOR_RED, COLOR_BLACK);  // Definir un par de colores personalizados adicionales para la opción seleccionada

    // Dibujar la pantalla antes de entrar en el bucle
    showMenu();
}

GUI::~GUI() {
    endwin();          // Finalizar ncurses al destruir la instancia de la clase
}

void GUI::clearScreen() {
    clear();
    refresh();
}

void GUI::showMenu() {
    int max_y, max_x;
    int current_option = 1;

    getmaxyx(stdscr, max_y, max_x); // Obtener el tamaño de la terminal

    std::vector<std::string> ascii_art = {
            "   __    ___                _                  __  ",
            "  / /   / / \\   _ __   __ _| |_   _ _______ _ _\\ \\ ",
            " / /   / / _ \\ | '_ \\ / _` | | | | |_  / _ \\ '__\\ \\",
            " \\ \\  / / ___ \\| | | | (_| | | |_| |/ /  __/ |  / /",
            "  \\_\\/\\/_/   \\_\\_| |_|\\__,_|_|\\__, /___\\___|_| /_/ ",
            "                              |___/                   "
        };

    do {
       clearScreen();
        // Calcular las coordenadas para centrar el menú
        int menu_y = (max_y - 11) / 2; // 7 líneas de texto en el menú
        int menu_x = (max_x - 40) / 2 ; // 15 caracteres en la longitud más larga del menú

        attron(COLOR_PAIR(1));
        // Imprimir el arte ASCII
        for (size_t i = 0; i < ascii_art.size(); ++i) {
            mvprintw(menu_y-7 + i, menu_x-5, ascii_art[i].c_str());
        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(1));
        mvprintw(menu_y - 1, menu_x - 1, "+----------------------------------------+");
        mvprintw(menu_y + 10, menu_x - 1, "+----------------------------------------+");
        for (int i = 0; i < 11; ++i) {
            mvprintw(menu_y + i, menu_x - 1, "|");
            mvprintw(menu_y + i, menu_x + 40, "|");
        }
        attroff(COLOR_PAIR(1));

        // Imprimir el menú con colores
        attron(COLOR_PAIR(1));
        mvprintw(menu_y + 1, menu_x, "1. Tags del HTML");
        mvprintw(menu_y + 2, menu_x, "2. Atributos de un tag");
        mvprintw(menu_y + 3, menu_x, "3. Enlaces de HTML");
        mvprintw(menu_y + 4, menu_x, "4. Imágenes de HTML");
        mvprintw(menu_y + 5, menu_x, "5. Guardar reporte");
        attroff(COLOR_PAIR(1));

        // Imprimir la opción actualmente seleccionada con colores diferentes
        attron(COLOR_PAIR(2));
        switch (current_option) {
            case 1:
                mvprintw(menu_y + 1, menu_x, "1. Tags del HTML");
                break;
            case 2:
                mvprintw(menu_y + 2, menu_x, "2. Atributos de un tag");
                break;
            case 3:
                mvprintw(menu_y + 3, menu_x, "3. Enlaces de HTML");
                break;
            case 4:
                mvprintw(menu_y + 4, menu_x, "4. Imágenes de HTML");
                break;
            case 5:
                mvprintw(menu_y + 5, menu_x, "5. Guardar reporte");
                break;
        }
        attroff(COLOR_PAIR(2));

        mvprintw(menu_y + 6, menu_x, "Seleccione una opción (w/s/enter) ");
        refresh();        // Actualizar la pantalla

        // Leer la tecla pulsada
        int ch = getch();

        if (ch == 'w' || ch == KEY_UP) {
            if (current_option > 1) {
                current_option--;
            }
        } else if (ch == 's' || ch == KEY_DOWN) {
            if (current_option < 5) {
                current_option++;
            }
        } else if (ch == '\n') {
            if (current_option >= 1 && current_option <= 5) {                
                handleOption(current_option);  // Manejar la opción seleccionad
            }
            
        }
    } while (true);
}

void GUI::handleOption(int option) {
    SubMenu subMenu;

    switch (option) {
        case 1:
            subMenu.tagsHtml(parser.getTagCounts());
            break;
        case 2:
            subMenu.atributosHtml();
            break;
        case 3:
            subMenu.enlacesHtml(parser.getLinks());
            break;
        case 4:
            subMenu.imagenesHtml();
            break;
    }
}


