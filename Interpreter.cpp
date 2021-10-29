#include "Interpreter.h"
#include <iostream>
#include <sstream>


Interpreter::Interpreter(DatalogProgram datalog) {
    this->datalog = datalog;
    // makes a database bases off the schemes, facts, and queries
    //Database database1();

    // make a relation for each scheme-Predicate, put that relation in database member
    makeSchemeRelations();
    // make a tuple for each fact predicate, put the tuple in the appropriate Relation in database
    makeFactTuples();

}

void Interpreter::makeDatabase(){

}

void Interpreter::run() {
    evaluateQueries();
}

void Interpreter::makeSchemeRelations() {
    std::vector<Predicates*> schemes = datalog.GetSchemes();
    for (unsigned int i = 0; i < schemes.size(); ++i){
        std::string name = schemes.at(i)->GetId();
        std::vector<Parameters*> parameters = schemes.at(i)->GetParameters();
        Header header;
        for(unsigned int j = 0; j < parameters.size(); ++j){
            header.addAttribute(parameters.at(j)->Getp());
        }
        Relation newRelation(name, header);
        database.addRelation(name, newRelation);
    }
}

void Interpreter::makeFactTuples() {
    std::vector<Predicates*> facts = datalog.GetFacts();
    for (unsigned int i = 0; i < facts.size(); ++i){
        std::string name;
        name = facts.at(i)->GetId();
        std::vector<Parameters*> parameters = facts.at(i)->GetParameters();
        Tuple tuple;
        for(unsigned int j = 0; j < parameters.size(); ++j){
            tuple.addString(parameters.at(j)->Getp());
        }
        database.addTupleToRelation(name, tuple);
    }
}

void Interpreter::evaluateQueries() {
    std::vector<Predicates*> queries = datalog.GetQueries();
    for (unsigned int i = 0; i < queries.size(); ++i) {
        std::cout << queries.at(i)->toString() << "? ";
        // yes or no
        std::cout << queriesToString(evaluatePredicate(*queries.at(i)));
    }

}

Relation Interpreter::evaluatePredicate(Predicates p) {
    std::map<std::string, int> variablesSeenMap;
    std::vector<std::string> variablesSeenVector;
    std::vector<int> seenIndices;
    bool varExists = false;
    //grab relation from the database
    std::string name = p.GetId();
    Relation originalRelation = database.getRelation(name);
    Relation newRelation = originalRelation;
    std::vector params = p.GetParameters();

    for (unsigned int i = 0; i < params.size(); ++i){
        varExists = false;
        if (params.at(i)->GetIsConstant() == true){
            newRelation = newRelation.selectIV(i ,params.at(i)->Getp());
        }
        else{
            int matchIndex;
            for (unsigned int j = 0; j < variablesSeenVector.size(); ++j){
                if(params.at(i)->Getp() == variablesSeenVector.at(j)){
                    // select 2
                    matchIndex = i;
                    varExists = true;
                }
            }
            if (varExists == true){
                newRelation = newRelation.selectII(variablesSeenMap[params.at(i)->Getp()] , matchIndex);
            }
            else {
                variablesSeenVector.push_back(params.at(i)->Getp());
                seenIndices.push_back(i);
                variablesSeenMap[params.at(i)->Getp()] = i;
            }
        }
    }
    newRelation = newRelation.project(seenIndices);
    newRelation = newRelation.rename(variablesSeenVector);
    return newRelation;
}


std::string Interpreter::queriesToString(Relation relation){
    std::stringstream ss;
    ss << relation.toString() << std::endl;
    return ss.str();
}
