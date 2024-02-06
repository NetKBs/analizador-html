#include "ErrorLens.hpp"
#include <stack>
#include <algorithm>

vector <string> ErrorLens::splitHtml(const string& html) {
    vector <string> lineasDeCodigo;
    string linea;

    for (char ch : html) {
        if (ch == '\n') {
            lineasDeCodigo.push_back(linea);
            linea = "";
        } else {
            linea += ch;
        }
    }
    if (!linea.empty()) {
        lineasDeCodigo.push_back(linea);
    }

    return lineasDeCodigo;
}

// Busca el caracter de cierre ">" de un tag de apertura o de cierre 
bool ErrorLens::caracterDeCerrado(vector <string> LineasDecodigo, size_t LineaIndex, size_t letraIndex){
    vector <string> codigo = LineasDecodigo;

    for (size_t linea = LineaIndex; linea < codigo.size(); linea++) {
        for (size_t i = letraIndex; i < codigo[linea].size(); i++) {
        
            if (codigo[linea][i] == '>') {
                return true;
            } else if (codigo[linea][i] == '<') { // Otra etiqueta iniciando
                return false;
            }
        }
    }
    return false;
}


vector <reporteError> ErrorLens::detectarErrores(const string& html) {
    vector <string> codigo = splitHtml(html); // lineas de codigo
    stack <string> tagsApertura;
    vector <reporteError> reportesError;

    for (size_t linea = 0; linea < codigo.size(); linea++) {
        for (size_t i = 0; i < codigo[linea].size(); i++) {
            
            // Saltar <!DOCTYPE>
            if (i + 1 < codigo[linea].size() && codigo[linea][i] == '<' && codigo[linea][i + 1] == '!') {
                break;
            }

            // Etiquetas de apertura
            if (i+1 < codigo[linea].size() && codigo[linea][i] == '<' && codigo[linea][i+1] != '/') {
             
                bool tagBienCerrado = caracterDeCerrado(codigo, linea, i+1);     
                if (!tagBienCerrado) {
                    reportesError.push_back({(int)linea+1, codigo[linea].erase(0, codigo[linea].find_first_not_of(' ')), ERROR_TIPO_1});

                } else {
                    string tag;
                    i++; // skip <
                    while(i < codigo[linea].size() && codigo[linea][i] != '>') {      
                        tag += codigo[linea][i];
                        i++;
                    }
                    // Chequear si es un tag sin etiqueta de cierre
                    if (find(tagsSinCierre.begin(), tagsSinCierre.end(), tag) == tagsSinCierre.end()) {
                        tagsApertura.push(tag);
                    }
                }   

            // Etiquetas de cierre
            } else if (i+1 < codigo[linea].size() && codigo[linea][i] == '<' && codigo[linea][i+1] == '/') {

                bool tagBienCerrado = caracterDeCerrado(codigo, linea, i+2);
                if (!tagBienCerrado) {
                    reportesError.push_back({(int)linea+1, codigo[linea].erase(0, codigo[linea].find_first_not_of(' ')), ERROR_TIPO_2});
                
                } else {
                    string tag;
                    i += 2;
                    while(i < codigo[linea].size() && codigo[linea][i] != '>') {
                        tag += codigo[linea][i];
                        i++;
                    }
                    if (tagsApertura.empty() || tagsApertura.top() != tag) {
                        reportesError.push_back({(int)linea+1, codigo[linea].erase(0, codigo[linea].find_first_not_of(' ')), ERROR_TIPO_3});
                    } else {
                        tagsApertura.pop();
                    }
                }
            }
            
    
        }

      

    }
    return reportesError;
}