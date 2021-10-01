#include "Rules.h"
#include "sstream"

Rules::Rules(Predicates* head) {
    this->headPredicate = head;
}

void Rules::SetName(std::string name) {
    this->name = name;
}
std::string Rules::GetName() {
    return name;
}

void Rules::AddHeadPredicate(Predicates *headP) {
    this->headPredicate = headP;
}

void Rules::AddBodyPredicate(Predicates *bodyP) {
    bodyPredicates.push_back(bodyP);
}

std::string Rules::toString() {
    std::stringstream ss;
    ss << "  " << headPredicate->toString() << " :- ";
    for (unsigned int i = 0; i < bodyPredicates.size(); ++i){
        //if (i != 0) ss << ",";
        ss << bodyPredicates.at(i)->toString();
        if (i == bodyPredicates.size() - 1) ss << ".";
        else ss << ",";
    }
    return ss.str();
}