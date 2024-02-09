#include <iostream>
#include "/home/manuelrg/Documentos/Programacion/analizador-html/src/datos/GestorDeArchivos.hpp"
#include "/home/manuelrg/Documentos/Programacion/analizador-html/src/negocio/HTMLParser.h"
#include "/home/manuelrg/Documentos/Programacion/analizador-html/src/presentacion/GUI.h"
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
    
    HTMLParser parser = HTMLParser(html);
    parser.extract();
    GUI gui = GUI(parser);
    gui.showMenu();
    
    
    

    return 0;
}
