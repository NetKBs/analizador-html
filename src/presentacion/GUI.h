#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>

#include "../negocio/HTMLParser.h"

/**
 * La clase GUI representa una interfaz gráfica de usuario.
 * Contiene métodos para mostrar un menú, limpiar la pantalla y manejar las opciones seleccionadas por el usuario.
 */
class GUI {
    private: 
        HTMLParser parser = HTMLParser("");

    public: 
        GUI(HTMLParser parser);
        ~GUI();
        void showMenu();
        void clearScreen();

    private: 
        void handleOption(int option);
};

#endif // GUI_H