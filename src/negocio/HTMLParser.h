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
   
    // Funciones para extraer los enlaces e imágenes...
    void parseHTML(const std::string& htmlContent);
    void extractLinks(GumboNode* node);
    void extractImages(GumboNode* node);

    std::map<std::string, std::pair<int, double>> countAndSortTags(GumboNode* node);


    // Métodos para acceder a los enlaces, imágenes, tag, etc
    const std::vector<std::string>& getLinks() const { return links; }
    const std::vector<std::string>& getImages() const { return images; }
    std::map<std::string, std::pair<int, double>> getTagCounts() const { return tagCounts; }
    std::vector<std::string> searchTag(GumboNode* node, const std::string& targetTag);

};

#endif // HTMLPARSER_HPP
