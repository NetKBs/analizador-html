#include <iostream>
#include "./datos/GestorDeArchivos.hpp"
#include "./negocio/HTMLParser.h"
#include "./presentacion/GUI.h"
#include "./negocio/ErrorLens.hpp"
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

    ErrorLens errorLens = ErrorLens();
    reporteError error = errorLens.detectarErrores(html);

    if (!error.muestraDeCodigo.empty()) {
        cout << error.muestraDeCodigo << endl;
        cout << "Error: " << error.error << endl;
        cout << "Linea: " << error.lineaError << endl;
        return 1;
    }
    /*
    HTMLParser parser = HTMLParser(html);
    parser.extract();
    GUI gui = GUI(parser);
    gui.showMenu();
    */
    

    return 0;
}
