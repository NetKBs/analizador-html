#ifndef HTMLPARSER_HPP
#define HTMLPARSER_HPP

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <gumbo.h>

/**
 * Clase HTMLParser para analizar y extraer información del contenido HTML.
 */
class HTMLParser {
private:
    std::vector<std::string> links;
    std::vector<std::string> images;
    std::map<std::string, std::pair<int, double>> tagCounts;

    GumboOutput* output;
    std::string htmlContent;

public:
   
    HTMLParser(const std::string& htmlContent);

    // Métodos para extraer la información
    void extract();
    void extractLinks(GumboNode* node);
    void extractImages(GumboNode* node);
    std::map<std::string, std::pair<int, double>> countAndSortTags(GumboNode* node);
    std::vector<std::string> searchTag(GumboNode* node, const std::string& targetTag);

    // Métodos para obtener la información
    const std::vector<std::string>& getLinks() const { return links; }
    const std::vector<std::string>& getImages() const { return images; }
    std::map<std::string, std::pair<int, double>> getTagCounts() const { return tagCounts; }
    std::vector<std::string> getTag(const std::string& targetTag);

};

#endif // HTMLPARSER_HPP
