#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter{
private:
    DatalogProgram datalog;
    Database database;
    Graph forwardGraph;
    Graph reverseGraph;
    std::vector<std::set<int>> SCCs;

public:
    Interpreter(DatalogProgram datalog);
    void run();
    void makeDatabase();
    void makeSchemeRelations();
    void makeFactTuples();
    void makeDependencyGraph();
    void makeSCCs();
    void evaluateRules();
    void evaluateRule(Rules &rule);
    void evaluateQueries();
    Relation evaluatePredicate(Predicates p);
    std::string rulesToString();
    std::string SCCToString(int index);
    std::string queriesToString(Relation relation);
    std::string toString();
};

#endif //PROJECT_1_INTERPRETER_H
