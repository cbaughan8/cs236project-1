#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
#include "Header.h"
#include "Tuple.h"
#include <string>
#include <set>
#include <vector>
#include <map>

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
    Relation unionR(Relation relation2);
    Relation join(Relation relation2);
    Header combineHeaders(Header header2, std::map<std::string, int> &columnPairs, std::vector<int> &nonMatchingAttributes);
    bool isJoinable(Tuple t1, Tuple t2, std::map<std::string, int> columnPairs);
    Tuple combineTuples(Tuple t1, Tuple t2, std::vector<int> nonMatchingAttributes);

    const std::set<Tuple> getTuples() const;
    Header getHeader();
    std::string toString();
    std::string unionedToString(Tuple t);

};

#endif //PROJECT_1_RELATION_H
