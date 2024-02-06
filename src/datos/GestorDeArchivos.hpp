#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <sstream>
#include <fstream>
using namespace std;

class GestorDeArchivos {

    private:
        stringstream buffer;
    public:
        string leerArchivoHTML(const string& rutaArchivo);
    
};

#endif