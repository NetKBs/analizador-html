#include "ErrorLens.hpp"
#include <iostream>
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
bool ErrorLens::caracterDeCerrado(vector <string> lineasDeCodigo, size_t LineaIndex, size_t letraIndex){

    for (size_t linea = LineaIndex; linea < lineasDeCodigo.size(); linea++) { 
        for (size_t i = letraIndex; i < lineasDeCodigo[linea].size(); i++) {

            if (lineasDeCodigo[linea][i] == '>') {
                return true;
            } else if (lineasDeCodigo[linea][i] == '<') { // Otra etiqueta iniciando
                return false;
            }
        }
        letraIndex = 0;
    }
    return false;
}


reporteError ErrorLens::detectarErrores(const string& html) {
    vector <string> lineasDeCodigo = splitHtml(html); 
    stack <pair<int,string>> tagsApertura;
    reporteError error;

    bool etiquetaScript = false;

    for (size_t linea = 0; linea < lineasDeCodigo.size(); linea++) {
        for (size_t i = 0; i < lineasDeCodigo[linea].size(); i++) {
            
            // Saltar <!DOCTYPE>
            if (i + 1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i + 1] == '!') {
                break;
            }

            // Ignorar si se está en busqueda de </script> 
            if (!etiquetaScript) {
                 // Etiquetas de apertura
                if (i+1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i+1] != '/') {
                
                    bool tagBienCerrado = caracterDeCerrado(lineasDeCodigo, linea, i+1);     
                    if (!tagBienCerrado) {
                        return  {(int)linea+1, lineasDeCodigo[linea], ERROR_TIPO_1};

                    } else {
                        string tag;
                        i++; // skip <
                        while(i < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] != '>' && lineasDeCodigo[linea][i] != ' ') {      
                            tag += lineasDeCodigo[linea][i];
                            i++;
                        }
                        // Chequear si es un tag que no lleva cierre
                        cout << tag << endl;
                        if (find(tagsSinCierre.begin(), tagsSinCierre.end(), tag) == tagsSinCierre.end()) {
                            if (tag == "script") {
                                etiquetaScript = true;
                            } 
                            tagsApertura.push({linea,tag});      
                        }
                    }   
                }
            }

            

            // Etiquetas de cierre
            else if (i+1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i+1] == '/') { 
               
                bool tagBienCerrado = caracterDeCerrado(lineasDeCodigo, linea, i+2);
                if (!tagBienCerrado) {
                    return  {(int)linea+1, lineasDeCodigo[linea], ERROR_TIPO_2};

                } else {
                    string tag;
                    i += 2; // skip </
                    while(i < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] != '>') {
                        tag += lineasDeCodigo[linea][i];
                        i++;
                    }

                    // Verificaciones
                    if (tagsApertura.empty()) { // No tiene tag de apertura
                        return {(int)linea+1, lineasDeCodigo[linea], ERROR_TIPO_3};
                    }
                    else if (tagsApertura.top().second != tag) {
                      
                        if (etiquetaScript) {
                            return {(int)tagsApertura.top().first+1, lineasDeCodigo[tagsApertura.top().first], ERROR_TIPO_4};
                        }

                        stack <pair<int, string>> aux;

                        while (!tagsApertura.empty()) {
                            aux.push(tagsApertura.top());
                            tagsApertura.pop();

                            if (!tagsApertura.empty()) {           
                                if (tagsApertura.top().second == tag) {
                                    return {(int)aux.top().first+1, lineasDeCodigo[aux.top().first], ERROR_TIPO_4};
                                }
                            }
                        }
                        return {(int)linea+1, lineasDeCodigo[linea], ERROR_TIPO_3};

                    } else {
                        if (etiquetaScript) {
                            etiquetaScript = false;
                        }
                        tagsApertura.pop();
                    }
                }
            }
        }
    }

    if (!tagsApertura.empty()) {
        return {tagsApertura.top().first+1, lineasDeCodigo[tagsApertura.top().first], ERROR_TIPO_3};
    }
    return {-1};
}
