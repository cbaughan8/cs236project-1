#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
#include "Header.h"
#include "Tuple.h"
#include <string>
#include <set>
#include <vector>

class Relation{
private:
    std::string name;
    Header header;
    std::set<Tuple> tuples;

public:
    Relation();
    Relation(std::string name, Header header);

    void addTuple(Tuple tuple);
    void addTuples(std::set<Tuple> tuples);
    Relation selectIV(int index, std::string value);
    Relation selectII(int index1, int index2);
    Relation project(std::vector<int> attributes);
    Relation rename(std::vector<std::string> replacers);
    std::string toString();

};

#endif //PROJECT_1_RELATION_H
