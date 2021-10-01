#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H
#include "Token.h"
#include "Predicates.h"
#include "Parameters.h"
#include "Rules.h"
#include <vector>

enum class ParsingStage{
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
};

class DatalogProgram{
private:
    std::vector<Token*> tokenList;
    unsigned int index;
    ParsingStage parsingStage;

    std::vector<Predicates*> schemes;
    std::vector<Predicates*> facts;
    std::vector<Predicates*> queries;
    std::vector<Predicates*> rulePredicates;
    std::vector<Rules*> rules;
    std::vector<Parameters*> tempParams;
    std::vector<std::string> domainParams;

    std::string tempText;
    std::string tempID;
    Parameters* tempParameter;
    //Predicates* tempPredicate;

public:
    DatalogProgram(std::vector<Token*> tokenList);
    ~DatalogProgram();
    void Init(DatalogProgram* self);
    void Match(TokenType tokenType);
    void Datalog(DatalogProgram* self);
    void Scheme();
    void SchemeList();
    void Fact();
    void FactList();
    void Rule();
    void RuleList();
    void Query();
    void QueryList();
    void HeadPredicate();
    void Predicate();
    void PredicateList();
    void Parameter();
    void ParameterList();
    void IdList();
    void StringList();
    void FindDomain();

    std::string SchemesToString();
    std::string FactsToString();
    std::string RulesToString();
    std::string QueriesToString();
    std::string DomainToString();
    std::string DatalogToString();
};

#endif //PROJECT_1_DATALOGPROGRAM_H
