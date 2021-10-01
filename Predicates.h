#ifndef PROJECT_1_PREDICATES_H
#define PROJECT_1_PREDICATES_H
#include "Parameters.h"
#include <string>
#include <vector>

class Predicates{
private:
    std::string name;
    std::string id;
    std::vector<Parameters*> parameters;

public:
    Predicates();
    Predicates(std::string name);
    void SetName(std::string name);
    std::string GetName();
    void AddId(std::string id);
    void AddParameter(Parameters* param);
    std::vector<Parameters*> GetParameters();
    std::string toString();
};

#endif //PROJECT_1_PREDICATES_H
