#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter{
private:
    DatalogProgram datalog;
    Database database;

public:
    Interpreter(DatalogProgram datalog);
    void run();
    void makeDatabase();
    void makeSchemeRelations();
    void makeFactTuples();
    void evaluateQueries();
    Relation evaluatePredicate(Predicates p);
    std::string queriesToString(Relation relation);
    std::string toString();

};

#endif //PROJECT_1_INTERPRETER_H
