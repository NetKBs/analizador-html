#include "GestorDeArchivos.hpp"

string GestorDeArchivos::leerArchivoHTML(const string &rutaArchivo) {
  ifstream archivo(rutaArchivo);
  if (!archivo) {
    return "";
  }

  buffer << archivo.rdbuf();
  return buffer.str();
}