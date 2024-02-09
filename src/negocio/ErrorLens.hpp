#ifndef ERROR_LENS_H
#define ERROR_LENS_H

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

enum errorEstados {
    ERROR_TIPO_1 = 1, // tag apertura sin >
        ERROR_TIPO_2, // tag cierre sin >
        ERROR_TIPO_3, // tag de cierre sin tag de apertura
        ERROR_TIPO_4 // tag de apertura sin tag de cierre
};

struct reporteError {
    int lineaError;
    string muestraDeCodigo;
    errorEstados error;
};

/**
 * Clase ErrorLens para detección e interpretación de errores en código HTML.
 */
class ErrorLens {

    private: 
        vector < string > tagsSinCierre = {
            "area",
            "base",
            "br",
            "col",
            "embed",
            "hr",
            "img",
            "input",
            "link",
            "meta",
            "param",
            "source",
            "track",
            "wbr"
        };

    public: 
        reporteError detectarErrores(const string & html);
        bool caracterDeCerrado(vector < string > lineasDeCodigo, size_t LineaIndex, size_t letraIndex);
        vector < string > splitHtml(const string & html);
        string interpretarError(errorEstados error);
};

#endif