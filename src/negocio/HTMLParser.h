#ifndef HTMLPARSER_HPP
#define HTMLPARSER_HPP

#include <iostream>
#include <vector>
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

    // Métodos para acceder a los enlaces e imágenes
    const std::vector<std::string>& getLinks() const { return links; }
    const std::vector<std::string>& getImages() const { return images; }
    std::vector<std::string> searchTag(GumboNode* node, const std::string& targetTag);
    std::map<std::string, std::pair<int, double>> countAndSortTags(GumboNode* node);
};

#endif // HTMLPARSER_HPP
