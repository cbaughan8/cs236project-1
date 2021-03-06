#ifndef PROJECT_1_RULES_H
#define PROJECT_1_RULES_H
#include "Predicates.h"
#include <vector>
#include <string>

class Rules{
private:
    std::string name;
    Predicates* headPredicate;
    std::vector<Predicates*> bodyPredicates;
public:
    Rules(Predicates* head);
    void SetName(std::string name);
    std::string GetName();
    std::vector<Predicates*> GetBodyPredicates();
    Predicates* getHeadPredicate();
    void AddHeadPredicate(Predicates* headP);
    void AddBodyPredicate(Predicates* bodyP);
    std::string toString();
};

#endif //PROJECT_1_RULES_H
