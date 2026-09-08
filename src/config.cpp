#include "config.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// to load in obj model
std::vector<std::string> split(std::string line, std::string delimiter) {
    
    std::vector<std::string> splitLine;

    size_t pos = 0;
    std::string token;
    // find where in line delimiter is, delimiter would be spaces, tokens would be words
    while((pos = line.find(delimiter)) != std::string::npos) { 
        // npos = impossible string index, indicates error when substring not found
        token = line.substr(0, pos); // slice from start of str, to position of delimiter
        splitLine.push_back(token);
        line.erase(0, pos + delimiter.size());
    }
    splitLine.push_back(line); // for final word with no space after it 

    return splitLine;
}