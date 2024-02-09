#include <stack>
#include <algorithm>
#include <sstream>

#include "ErrorLens.hpp"


string ErrorLens::interpretarError(errorEstados error) {
    vector < string > tiposErrores = {
        "Etiqueta de apertura mal formada",
        "Etiqueta de cierre mal formada",
        "Etiqueta de cierre sin etiqueta de apertura",
        "Etiqueta de apertura sin etiqueta de cierre"
    };
    return tiposErrores[error - 1];
}

vector<string> ErrorLens::splitHtml(const string& html) {
    vector<string> lineasDeCodigo;
    stringstream ss(html);
    string linea;

    while (getline(ss, linea, '\n')) {
        lineasDeCodigo.push_back(linea);
    }
    return lineasDeCodigo;
}

bool ErrorLens::caracterDeCerrado(const vector<string> lineasDeCodigo, size_t LineaIndex, size_t letraIndex) {
    for (size_t linea = LineaIndex; linea < lineasDeCodigo.size(); linea++) {
        const string& line = lineasDeCodigo[linea];
        for (size_t i = letraIndex; i < line.size(); i++) {
            if (line[i] == '>') {
                return true;
            } else if (line[i] == '<') { // Otra etiqueta iniciando
                return false;
            }
        }
        letraIndex = 0;
    }
    return false;
}

reporteError ErrorLens::detectarErrores(const string & html) {
    vector < string > lineasDeCodigo = splitHtml(html);
    stack < pair < int, string >> tagsApertura;
    reporteError error;

    bool etiquetaScript = false; // flag

    for (size_t linea = 0; linea < lineasDeCodigo.size(); linea++) {
        for (size_t i = 0; i < lineasDeCodigo[linea].size(); i++) {

            // Saltar <!
            if (i + 1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i + 1] == '!') {
                break;
            }

            // Buscar </script> dentro de la línea
            if (etiquetaScript) { 
                if (i + 1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i + 1] == '/') {
                    string tag;
                        i += 2; // skip </
                        while (i < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] != '>') {
                            tag += lineasDeCodigo[linea][i];
                            i++;
                        }
                    if (tag == "script" ) {
                        etiquetaScript = false;
                        tagsApertura.pop();
                    }
                }
            }

            // Ignorar si se está en busqueda de </script> 
            if (!etiquetaScript) {
                // Etiquetas de apertura
                if (i + 1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i + 1] != '/') {

                    bool tagBienCerrado = caracterDeCerrado(lineasDeCodigo, linea, i + 1);
                    if (!tagBienCerrado) {
                        cout << lineasDeCodigo[linea]<<endl;
                        return {(int) linea + 1, lineasDeCodigo[linea],ERROR_TIPO_1};

                    } else {
                        string tag;
                        i++; // skip <
                        while (i < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] != '>' && lineasDeCodigo[linea][i] != ' ') {
                            tag += lineasDeCodigo[linea][i];
                            i++;
                        }
                        // Chequear si es un tag que no lleva cierre        
                        if (find(tagsSinCierre.begin(), tagsSinCierre.end(), tag) == tagsSinCierre.end()) {
                            if (tag == "script") {
                                etiquetaScript = true;
                            }
                            tagsApertura.push({linea,tag});
                        }
                    }
                }

                // Etiquetas de cierre
                if (i + 1 < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] == '<' && lineasDeCodigo[linea][i + 1] == '/') {

                    bool tagBienCerrado = caracterDeCerrado(lineasDeCodigo, linea, i + 2);
                    if (!tagBienCerrado) {
                        return {(int) linea + 1, lineasDeCodigo[linea], ERROR_TIPO_2};

                    } else {
                        string tag;
                        i += 2; // skip </
                        while (i < lineasDeCodigo[linea].size() && lineasDeCodigo[linea][i] != '>') {
                            tag += lineasDeCodigo[linea][i];
                            i++;
                        }

                        // Verificaciones
                        if (tagsApertura.empty()) { // No tiene tag de apertura
                            return {(int) linea + 1, lineasDeCodigo[linea], ERROR_TIPO_3};

                        } else if (tagsApertura.top().second != tag) {
                            stack < pair < int, string >> aux;

                            while (!tagsApertura.empty()) {
                                aux.push(tagsApertura.top());
                                tagsApertura.pop();

                                if (!tagsApertura.empty()) {
                                    if (tagsApertura.top().second == tag) {
                                        return {(int) aux.top().first + 1, lineasDeCodigo[aux.top().first], ERROR_TIPO_4};
                                    }
                                }
                            }
                            return {(int) linea + 1, lineasDeCodigo[linea], ERROR_TIPO_3};

                        } else {
                            tagsApertura.pop();
                        }
                    }
                }
            }
        }
    }

    if (etiquetaScript) { // Nunca se encontró </script>
        return {
            (int) tagsApertura.top().first + 1,
            lineasDeCodigo[tagsApertura.top().first],
            ERROR_TIPO_4
        };
    }

    if (!tagsApertura.empty()) { // Etiquetas sin cerrado
        return {
            tagsApertura.top().first + 1,
            lineasDeCodigo[tagsApertura.top().first],
            ERROR_TIPO_3
        };
    }
    return {-1};
}