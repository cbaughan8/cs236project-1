#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H
#include "Relation.h"
#include <map>


class Database{
private:
    std::map<std::string, Relation> relationMap;
public:
    Database();
    void addRelation(std::string name, Relation relation);
    void addTupleToRelation(std::string name, Tuple tuple);
    Relation getRelation(std::string name);

};

#endif //PROJECT_1_DATABASE_H
