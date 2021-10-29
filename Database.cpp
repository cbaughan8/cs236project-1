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

Relation Database::getRelation(std::string name) {
    return relationMap[name];
}
