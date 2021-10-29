#include "Header.h"
#include <sstream>

void Header::addAttribute(std::string attribute) {
    attributes.push_back(attribute);
}

std::string Header::getAttribute(int index) {
    return attributes.at(index);
}

std::vector<std::string> Header::getAttributeVector() {
    return attributes;
}

void Header::setAttribute(int index, std::string value) {
    attributes.at(index) = value;
}

std::string Header::toString() {
    std::stringstream ss;
    for(unsigned int i = 0; i < attributes.size(); ++i){
        ss << attributes.at(i);
        if (i != attributes.size() - 1) ss << ",";
    }
    return ss.str();
}