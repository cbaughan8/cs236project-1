#include "Database.h"
#include <sstream>

Database::Database() {

}

void Database::addRelation(std::string name, Relation relation) {
    relationMap[name] = relation;
}

void Database::addTupleToRelation(std::string name, Tuple tuple) {
    relationMap[name].addTuple(tuple);
}

void Database::setRelation(const std::string &name, Relation newRelation) {
    /*std::map<std::string, Relation>::iterator it = relationMap.find(name);
    if (it != relationMap.end()){
        it->second = newRelation;
    }*/
    relationMap[name] = newRelation;
}


int Database::tupleCount() {
    int count = 0;
    for (auto const& x: relationMap)
    {
        count += x.second.getTuples().size();
    }
    return count;
}

Relation Database::getRelation(std::string name) {
    return relationMap[name];
}
