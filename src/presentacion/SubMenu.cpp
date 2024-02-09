// SubMenu.cpp
#include "SubMenu.h"
#include <cctype>
#include <cstring>
#include <ncurses.h>

SubMenu::SubMenu() {
  initscr();
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
}

SubMenu::~SubMenu() { endwin(); }

void SubMenu::clearScreen() {
  clear();
  refresh();
}

void SubMenu::imprimirMarco(string titulo) {
  int terminal_width = COLS;   // Ancho de la terminal
  int terminal_height = LINES; // Altura de la terminal

  clearScreen();
  attron(COLOR_PAIR(1));
  // Top border
  mvprintw(0, 0, "+");
  for (int i = 1; i < terminal_width - 1; ++i) {
    mvprintw(0, i, "-");
  }
  mvprintw(0, terminal_width - 1, "+");
  // Side borders
  for (int i = 1; i < terminal_height - 1; ++i) {
    mvprintw(i, 0, "|");
    mvprintw(i, terminal_width - 1, "|");
  }
  // Bottom border
  mvprintw(terminal_height - 1, 0, "+");
  for (int i = 1; i < terminal_width - 1; ++i) {
    mvprintw(terminal_height - 1, i, "-");
  }
  mvprintw(terminal_height - 1, terminal_width - 1, "+");
  // Title
  mvprintw(1, (COLS - strlen(titulo.c_str())) / 2, titulo.c_str());
  attroff(COLOR_PAIR(1));
  refresh();
}

void SubMenu::tagsHtml(map<string, pair<int, double>> conteoEtiquetas) {

  if (conteoEtiquetas.empty()) {
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron etiquetas");
    refresh();
    getch();
    return;
  }

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int columna_media = COLS / 2;
  int cantidadEtiquetas = conteoEtiquetas.size();

  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; 

  while (indice < cantidadEtiquetas) {
    clear(); 
    imprimirMarco("TAGS DEL HTML");
    mvprintw(fila, columna + 10, "Etiqueta");
    mvprintw(fila, columna_media - 3, "Cantidad");
    mvprintw(fila, columna + 45, "Porcentaje");
    mvprintw(fila + 1, columna + 9,
             "-----------------------------------------------");

    for (int i = 0; i < elementosPorPagina && indice < cantidadEtiquetas; ++i) {
      auto it = std::next(conteoEtiquetas.begin(), indice); // Avanzar el iterador a la posición correcta
      mvprintw(fila + 2, columna + 10, "%-20s", it->first.c_str());
      mvprintw(fila + 2, columna_media - 3, "%-19d", it->second.first);
      mvprintw(fila + 2, columna + 45, "%.2f %%", it->second.second);
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();

    int continuar = getch();
    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}

void SubMenu::buscarUnTag(HTMLParser parser) {

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una página

  imprimirMarco("");
  attron(COLOR_PAIR(1));
  echo(); // Habilitar el eco de los caracteres ingresados por el usuariomvprin
  mvprintw(LINES / 2 - 10, COLS / 2 - 10, "BUSCAR UN TAG");
  mvprintw(LINES / 2 - 10 + 2, COLS / 2 - 15, ">>> ");
  attroff(COLOR_PAIR(1));

  char userInput[256];
  getnstr(userInput, sizeof(userInput) - 1);
  noecho(); // Deshabilitar el eco de los caracteres

  vector<string> etiquetas = parser.getTag(userInput);
  if (etiquetas.empty()) {
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron etiquetas");
    refresh();
    getch();
    return;
  }

  int cantidadEtiquetas = etiquetas.size();
  while (indice < cantidadEtiquetas) {
    imprimirMarco("");

    for (int i = 0; i < elementosPorPagina && indice < cantidadEtiquetas; ++i) {

      if (etiquetas[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] <%s>", indice + 1, (etiquetas[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] <%s>", indice + 1, etiquetas[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();

    int continuar = getch();
    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}

void SubMenu::enlacesHtml(vector<string> links) {

  if(links.empty()){
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron enlaces");
    refresh();
    getch();
    return;
  }

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int cantidadLinks = links.size();
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una 

  while (indice < cantidadLinks) {
    clear(); // Borra la pantalla antes de imprimir la siguiente página
    imprimirMarco("ENLACES EN EL HTML");

    for (int i = 0; i < elementosPorPagina && indice < cantidadLinks; ++i) {

      if (links[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] %s", indice + 1, (links[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] %s", indice + 1, links[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();
    int continuar = getch();

    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}

void SubMenu::imagenesHtml(vector<string> imagenes) {

  if (imagenes.empty()) {
    clear();
    mvprintw(LINES / 2 - 10, COLS / 2 - 10, "No se encontraron imágenes");
    refresh();
    getch();
    return;
  }

  int fila = 3;
  int columna = (COLS - 60) / 2;
  int cantidadImagenes = imagenes.size();
  int indice = 0;
  int pagina = 0;
  int elementosPorPagina = LINES - 10; // Calcula cuántos elementos caben en una página

  while (indice < cantidadImagenes) {
    clear(); // Borra la pantalla antes de imprimir la siguiente página
    imprimirMarco("IMAGENES EN EL HTML");

    for (int i = 0; i < elementosPorPagina && indice < cantidadImagenes; ++i) {

      if (imagenes[indice].length() > COLS - 10) {
        mvprintw(fila, 2, "[%d] %s", indice + 1,
                 (imagenes[indice].substr(0, COLS - 15) + "...").c_str());
      } else {
        mvprintw(fila, 2, "[%d] %s", indice + 1, imagenes[indice].c_str());
      }
      ++fila;
      ++indice;
    }

    mvprintw(LINES - 3, columna - 3, "<< Página %d - Presione 'q' para salir o 'cualquier tecla' para continuar >>", pagina + 1);
    refresh();

    int continuar = getch();
    if (continuar == 'q') {
      return;
    }
    fila = 3;
    ++pagina;
  }
}