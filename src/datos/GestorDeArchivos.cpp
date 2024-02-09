#include "GestorDeArchivos.hpp"
#include <iostream>

std::string GestorDeArchivos::leerArchivoHTML(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo) {
        return "";
    }

    std::stringstream buffer;
    buffer << archivo.rdbuf();
    archivo.close();

    return buffer.str();
}

void GestorDeArchivos::guardarAnalisis(const HTMLParser& parser, const std::string& rutaArchivoSalida) {
    std::ofstream archivoSalida(rutaArchivoSalida);
    if (!archivoSalida.is_open()) {
        // Manejar error al abrir el archivo de salida
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return;
    }

    // Obtener información del análisis del HTMLParser
    std::map<std::string, std::pair<int, double>> tagCounts = parser.getTagCounts();
    std::vector<std::string> links = parser.getLinks();
    std::vector<std::string> images = parser.getImages();

    // Escribir la información en el archivo de salida
    archivoSalida << "Tags del HTML:" << std::endl;
    for (const auto& pair : tagCounts) {
        archivoSalida << pair.first << ": " << pair.second.first << " veces, " << pair.second.second << "%" << std::endl;
    }

    archivoSalida << "\nEnlaces de HTML:" << std::endl;
    for (const std::string& link : links) {
        archivoSalida << link << std::endl;
    }

    archivoSalida << "\nImágenes de HTML:" << std::endl;
    for (const std::string& image : images) {
        archivoSalida << image << std::endl;
    }

    // Cerrar el archivo de salida
    archivoSalida.close();
}