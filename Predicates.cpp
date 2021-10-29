#include "Predicates.h"
#include "sstream"

Predicates::Predicates() {

}

Predicates::Predicates(std::string name) {
    this->name = name;
}

void Predicates::SetName(std::string name) {
    this->name = name;
}
std::string Predicates::GetName() {
    return name;
}

std::string Predicates::GetId() {
    return id;
}

void Predicates::AddParameter(Parameters* param) {
    parameters.push_back(param);
}

void Predicates::AddId(std::string id) {
    this->id = id;
}

std::vector<Parameters*> Predicates::GetParameters(){
    return parameters;
}

std::string Predicates::toString() {
    std::stringstream ss;
    ss << id << "(";
    for (unsigned int i = 0; i < parameters.size(); ++i){
        if (i != 0) ss << ",";
        ss << parameters.at(i)->toString();
    }
    ss << ")";
    return ss.str();
}