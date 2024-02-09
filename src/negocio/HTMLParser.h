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

    GumboOutput* output;
    std::string htmlContent;

public:
   

    HTMLParser(const std::string& htmlContent);
    //~HTMLParser();

    // Funciones para extraer los enlaces e imágenes...
    void extract();
    void extractLinks(GumboNode* node);
    void extractImages(GumboNode* node);
    std::map<std::string, std::pair<int, double>> countAndSortTags(GumboNode* node);
    std::vector<std::string> searchTag(GumboNode* node, const std::string& targetTag);


    // Métodos para acceder a los enlaces, imágenes, tag, etc
    const std::vector<std::string>& getLinks() const { return links; }
    const std::vector<std::string>& getImages() const { return images; }
    std::map<std::string, std::pair<int, double>> getTagCounts() const { return tagCounts; }
    std::vector<std::string> getTag(const std::string& targetTag);

};

#endif // HTMLPARSER_HPP
