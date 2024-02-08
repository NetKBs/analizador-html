#include <iostream>
#include "./datos/GestorDeArchivos.hpp"
#include "./negocio/HTMLParser.h"
#include "./presentacion/GUI.h"
#include "negocio/HTMLParser.h"
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <file_path>\n";
        return 1;
    }

    string html = GestorDeArchivos().leerArchivoHTML(argv[1]);
    if (html == "") {
        cerr  << "No se pudo leer el archivo: " << argv[1] << std::endl;
        return 1;
    }
    
    HTMLParser parser;
    parser.parseHTML(html);
    GUI gui = GUI(parser);
    gui.showMenu();
    
    
    

    return 0;
}
