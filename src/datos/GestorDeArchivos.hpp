#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <sstream>
#include <fstream>

#include "../negocio/HTMLParser.h"  
using namespace std;

/**
 * Clase GestorDeArchivo para la manipulación con archivos.
 */
class GestorDeArchivos {

    private:
        stringstream buffer;
    public:
          std::string leerArchivoHTML(const std::string& rutaArchivo);
          void guardarAnalisis(const HTMLParser& parser, const std::string& rutaArchivoSalida);
};

#endif