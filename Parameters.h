#ifndef PROJECT_1_PARAMETERS_H
#define PROJECT_1_PARAMETERS_H

#include <string>

class Parameters{
private:
    std::string p;
    bool isConstant;
public:
    Parameters();
    Parameters(std::string p);
    void Setp(std::string p);
    std::string Getp();
    bool GetIsConstant();
    std::string toString();
};

#endif //PROJECT_1_PARAMETERS_H
