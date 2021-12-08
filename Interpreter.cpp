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
    makeDependencyGraph();
    makeSCCs();
    evaluateRules();
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

void Interpreter::makeDependencyGraph() {
    std::cout << "Dependency Graph" << std::endl;
    std::vector<Rules*> rules = datalog.GetRules();
    Graph graph(rules);
    forwardGraph = graph;
    reverseGraph = graph;

    for (unsigned int i = 0; i < rules.size(); i++){
        for (unsigned int j = 0; j < rules.at(i)->GetBodyPredicates().size(); j++){
            for (unsigned int k = 0; k < rules.size(); k++){
                if (rules.at(k)->getHeadPredicate()->GetId() == rules.at(i)->GetBodyPredicates().at(j)->GetId()){
                    forwardGraph.addEdge(i, k);
                    reverseGraph.addEdge(k, i);
                }
            }
        }
    }
    std::cout << forwardGraph.dependenciesToString() << std::endl;
    // std::cout << reverseGraph.dependenciesToString();
}

void Interpreter::makeSCCs() {
    std::stack<int> postorder;
    std::vector<int> reversePostorder;
    postorder = reverseGraph.dfsForestPostorder();
    std::stringstream ss;

    while(!postorder.empty()) {
        // ss << postorder.top() << " ";
        reversePostorder.push_back(postorder.top());
        postorder.pop();
    }
    //std::cout << ss.str() << std::endl;
    SCCs = forwardGraph.dfsForestSCC(reversePostorder);
}

void Interpreter::evaluateRules(){
    std::cout << "Rule Evaluation" << std::endl;
    std::vector<Rules*> rules = datalog.GetRules();
    int countBefore;
    bool tuplesAdded = true;
    // if SCC has one node and that node isn't self-dependent, only evaluate once
    // else evaluate SCC in fixed point algorithm
    // maybe use set.fint(itself)

    for (unsigned int i = 0; i < SCCs.size(); i++){
        int passes = 0;
        std::cout << "SCC: ";
        std::cout << SCCToString(i) << std::endl;
        tuplesAdded = true;
        while(tuplesAdded){
            passes++;
            tuplesAdded = false;
            countBefore = database.tupleCount();
            for (int node : SCCs.at(i)){
                Rules rule = *rules.at(node);
                evaluateRule(rule);
            }
            int countAfter = database.tupleCount();
            if(countBefore != countAfter) tuplesAdded = true;
            if(SCCs.at(i).size() == 1){
                for (int node : SCCs.at(i)){
                    if (forwardGraph.getAdjNodes(node).empty()) tuplesAdded = false;
                    else{
                        bool reflecting = false;
                        for (int adjNode : forwardGraph.getAdjNodes(node)){
                            if(node == adjNode){
                                reflecting = true;
                            }
                        }
                        for (int adjNode : forwardGraph.getAdjNodes(node)){
                            if(node != adjNode && (forwardGraph.getAdjNodes(node).size() <= 1 || !reflecting)){
                                tuplesAdded = false;
                            }
                        }
                    }
                }
            }
        }
        std::cout << passes << " passes: ";
        std::cout << SCCToString(i) << std::endl;
    }

    // project 4 fixed point
    /*while(tuplesAdded){
        passes++;
        tuplesAdded = false;
        countBefore = database.tupleCount();
        for (unsigned int i = 0; i < rules.size(); i++){
            Rules rule = *rules.at(i);
            evaluateRule(rule);
        }
        int countAfter = database.tupleCount();
        if(countBefore != countAfter) tuplesAdded = true;
    }*/

}

void Interpreter::evaluateRule(Rules &rule){
    Relation newRelation;
    std::vector<Relation> BPRelations;
    std::cout << rule.toString() << std::endl;
    for (unsigned int j = 0; j < rule.GetBodyPredicates().size(); j++){
        BPRelations.push_back(evaluatePredicate(*rule.GetBodyPredicates().at(j)));
    }
    newRelation = BPRelations.at(0);
    if (rule.GetBodyPredicates().size() > 1){
        for (unsigned int j = 1; j < BPRelations.size(); j++){
            newRelation = newRelation.join(BPRelations.at(j));
        }
    }
    Predicates headPredicate = *rule.getHeadPredicate();

    std::vector<int> projectIndices;
    std::vector<std::string> renameReplacers;
    for (unsigned int k = 0; k < headPredicate.GetParameters().size(); k++){
        for (unsigned int j = 0; j < newRelation.getHeader().size(); j++){
            // save indices of header
            if (headPredicate.GetParameters().at(k)->Getp() == newRelation.getHeader().getAttribute(j)){
                projectIndices.push_back(j);
                renameReplacers.push_back(newRelation.getHeader().getAttribute(j));
            }
        }
    }
    newRelation = newRelation.project(projectIndices);
    newRelation = newRelation.rename(renameReplacers);
    // newRelation = newRelation.unionR(database.getRelation(headPredicate.GetId()));
    newRelation = database.getRelation(headPredicate.GetId()).unionR(newRelation);
    // std::cout << newRelation.toString() << std::endl;
    database.setRelation(headPredicate.GetId(), newRelation);
}

void Interpreter::evaluateQueries() {
    std::vector<Predicates*> queries = datalog.GetQueries();
    std::cout << std::endl << "Query Evaluation" << std::endl;
    for (unsigned int i = 0; i < queries.size(); ++i) {
        std::cout << queries.at(i)->toString() << "? ";
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
        if (params.at(i)->GetIsConstant()){
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

std::string Interpreter::SCCToString(int index) {
    std::stringstream ss;
    bool comma = false;
    for (int node : SCCs.at(index)){
        if (comma) {
            std::cout << ",";
        }
        comma = true;
        std::cout << "R" << node;
    }
    return ss.str();
}

std::string Interpreter::queriesToString(Relation relation){
    std::stringstream ss;
    ss << relation.toString() << std::endl;
    return ss.str();
}

