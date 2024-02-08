#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <gumbo.h>


class HTMLParser {
private:
    std::vector<std::string> links;
    std::vector<std::string> images;
    std::map<std::string, std::pair<int, double>> tagCounts;
    std::vector<std::string> lines;

public:
    // Constructor
    HTMLParser();

    // Funciones para extraer los enlaces e imágenes...
    void parseHTML(const std::string& htmlContent);
    void extractLinks(GumboNode* node);
    void extractImages(GumboNode* node);
    std::vector<std::string> searchTag(GumboNode* node, const std::string& targetTag);
    std::map<std::string, std::pair<int, double>> countAndSortTags(GumboNode* node);

    // Métodos para acceder a los enlaces e imágenes
    const std::vector<std::string>& getLinks() const { return links; }
    const std::vector<std::string>& getImages() const { return images; }
};


void HTMLParser::parseHTML(const std::string& htmlContent) {
    GumboOutput* output = gumbo_parse(htmlContent.c_str());
    extractLinks(output->root);
    extractImages(output->root);
    tagCounts = countAndSortTags(output->root);
    gumbo_destroy_output(&kGumboDefaultOptions, output);
}

//Extraer enlaces
void HTMLParser::extractLinks(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
        links.push_back(href->value);
    }
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        extractLinks(static_cast<GumboNode*>(children->data[i]));
    }
}

//Extraer Imagenes
void HTMLParser::extractImages(GumboNode* node) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    GumboAttribute* src;
    if (node->v.element.tag == GUMBO_TAG_IMG &&
        (src = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
        images.push_back(src->value);
    }
    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        extractImages(static_cast<GumboNode*>(children->data[i]));
    }
}

//Dado un tag, mostrar sus atributos
std::vector<std::string> HTMLParser::searchTag(GumboNode* node, const std::string& targetTag) {
    std::vector<std::string> lines;

    if (node->type != GUMBO_NODE_ELEMENT) {
        return lines;
    }

    GumboElement* element = &node->v.element;
    std::string tagname(gumbo_normalized_tagname(element->tag));

    // Verificar si el tag coincide con el que estamos buscando
    if (tagname == targetTag) {
        // Obtener la línea de código que contiene el tag y sus atributos
        std::string line = gumbo_normalized_tagname(element->tag);
        GumboVector* attributes = &element->attributes;
        for (unsigned int i = 0; i < attributes->length; ++i) {
            GumboAttribute* attribute = static_cast<GumboAttribute*>(attributes->data[i]);
            line += " " + std::string(attribute->name) + "=\"" + std::string(attribute->value) + "\"";
        }
        lines.push_back(line);
    }

    // Recorrer los hijos recursivamente
    GumboVector* children = &element->children;
    for (unsigned int i = 0; i < children->length; ++i) {
        std::vector<std::string> childLines = searchTag(static_cast<GumboNode*>(children->data[i]), targetTag);
        lines.insert(lines.end(), childLines.begin(), childLines.end());
    }

    return lines;
}

//Tags por orden alfabetico, frecuencia y %
std::map<std::string, std::pair<int, double>> HTMLParser::countAndSortTags(GumboNode* node) {
    std::map<std::string, std::pair<int, double>> tagCounts;

    if (node->type != GUMBO_NODE_ELEMENT) {
        return tagCounts;
    }

    GumboElement* element = &node->v.element;
    std::string tagname(gumbo_normalized_tagname(element->tag));

    // Contar la frecuencia del tag
    tagCounts[tagname].first++;

    // Recorrer los hijos recursivamente
    GumboVector* children = &element->children;
    for (unsigned int i = 0; i < children->length; ++i) {
        std::map<std::string, std::pair<int, double>> childTagCounts = countAndSortTags(static_cast<GumboNode*>(children->data[i]));
        for (const auto& pair : childTagCounts) {
            tagCounts[pair.first].first += pair.second.first;
        }
    }

    // Calcular el total de tags
    int totalTags = 0;
    for (const auto& pair : tagCounts) {
        totalTags += pair.second.first;
    }

    // Calcular el porcentaje de frecuencia de cada tag
    for (auto& pair : tagCounts) {
        pair.second.second = (static_cast<double>(pair.second.first) / totalTags) * 100.0;
    }

    return tagCounts;
}
