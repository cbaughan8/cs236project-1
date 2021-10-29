#include "Parameters.h"
#include "sstream"

Parameters::Parameters() {

}

Parameters::Parameters(std::string p) {
    this->p = p;
    if (p.substr(0, 1) == "'") isConstant = true;
}

void Parameters::Setp(std::string p) {
    this->p = p;
    if (p.substr(0, 1) == "'") isConstant = true;
    else isConstant = false;
}
std::string Parameters::Getp() {
    return p;
}

bool Parameters::GetIsConstant(){
    return isConstant;
}


std::string Parameters::toString() {
    std::stringstream ss;
    ss << p;
    return ss.str();
}

