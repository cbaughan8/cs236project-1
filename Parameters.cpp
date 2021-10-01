#include "Parameters.h"
#include "sstream"

Parameters::Parameters() {

}

Parameters::Parameters(std::string p) {
    this->p = p;
}

void Parameters::Setp(std::string p) {
    this->p = p;
}
std::string Parameters::Getp() {
    return p;
}


std::string Parameters::toString() {
    std::stringstream ss;
    ss << p;
    return ss.str();
}

