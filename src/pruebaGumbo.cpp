#include "gumbo.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
#include <algorithm>



std::string leerArchivoHTML(const std::string& rutaArchivo) {
  std::ifstream archivo(rutaArchivo);
  if (!archivo) {
    std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << archivo.rdbuf();
  return buffer.str();
}
/*
// Function to Auto complete the missing tag in the HTML Code
std::string autoComplete(const std::string& s) {
    // Split the html Code into lines
    std::vector<std::string> linesOfCode;
    std::string line;
    for (char ch : s) {
        if (ch == '\n') {
            linesOfCode.push_back(line);
            line = "";
        } else {
            line += ch;
        }
    }
    if (!line.empty()) {
        linesOfCode.push_back(line);
    }
 
    // Tags which are self-closed and don't need closing
    std::vector<std::string> selfClosedTags = {"area", "base", "br", "col", 
                                               "embed", "hr", "img", "input", 
                                               "link", "meta", "param", "source", 
                                               "track", "wbr"};
 
    std::stack<std::string> stack;
 
    // Loop to iterate over the lines of code
    for (const std::string& line : linesOfCode) {
        for (size_t j = 0; j < line.size();) {
            // Check for end tags
            if (j + 1 < line.size() && line[j] == '<' && line[j + 1] == '/') {
                std::string tag;
                j += 2;
                while (j < line.size() && line[j] >= 'a' && line[j] <= 'z') {
                    tag += line[j];
                    j++;
                }
                while (j < line.size() && line[j] != '>') {
                    j++;
                }
                if (!stack.empty() && stack.top() != tag) {
                    return "</" + stack.top() + ">";
                }
                stack.pop();
            }
            // Skip the HTML 5 condition
            else if (j + 1 < line.size() && line[j] == '<' && line[j + 1] == '!') {
                j += 2;
            }
            // Check for start tags
            else if (line[j] == '<') {
                std::string tag;
                j++;
                while (j < line.size() && line[j] >= 'a' && line[j] <= 'z') {
                    tag += line[j];
                    j++;
                }
                while (j < line.size() && line[j] != '>') {
                    j++;
                }
                if (std::find(selfClosedTags.begin(), 
                              selfClosedTags.end(), tag) == selfClosedTags.end()) {
                    stack.push(tag);
                }
            }
            j++;
        }
    }
 
    // Check if any tag is unbalanced then return that tag
    if (!stack.empty()) {
        return "</" + stack.top() + ">";
    }
    return "-1";
}
 
*/



int main() {
    std::string html = leerArchivoHTML("ejemplo.html");
  if (html.empty()) {
    return 1;  // Error al leer el archivo.
  }
   
    std::string tag = autoComplete(html);
    std::cout << tag << std::endl;
    return 0;

}
