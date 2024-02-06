#include <iostream>
#include "./datos/GestorDeArchivos.hpp"
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
    
    cout << html << endl;

    return 0;
}
