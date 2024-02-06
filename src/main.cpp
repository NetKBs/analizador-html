#include <iostream>
#include "./datos/GestorDeArchivos.hpp"
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
 
    vector <reporteError> reportesError = ErrorLens().detectarErrores(html);

    for (reporteError reporte : reportesError) {
        cout << "Error Linea " << reporte.lineaError << " "; 
        cout << reporte.muestraDeCodigo << " TIPO:" << reporte.error << endl;
    }

    return 0;
}
