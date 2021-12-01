#include "Tuple.h"
#include <sstream>

Tuple::Tuple() {

}

void Tuple::addString(std::string value) {
    strings.push_back(value);
}

std::string Tuple::getString(int index) {
    return strings.at(index);
}

void Tuple::setStrings(std::vector<std::string> newStrings) {
    strings = newStrings;
}

std::vector<std::string> Tuple::getStrings() {
    return strings;
}

size_t Tuple::size(){
    return strings.size();
}

std::string Tuple::toString() {
    std::stringstream ss;
    for(unsigned int i = 0; i < strings.size(); ++i){
        ss << strings.at(i);
        if (i != strings.size() - 1) ss << ",";
    }
    return ss.str();
}

