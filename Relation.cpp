#include "Relation.h"
#include <iostream>
#include <sstream>

Relation::Relation() {

}

Relation::Relation(std::string name, Header header) {
    this->name = name;
    this->header = header;
}

void Relation::addTuple(Tuple tuple) {
    tuples.insert(tuple);
}

void Relation::addTuples(std::set<Tuple> tuples) {
    this->tuples = tuples;
}

Relation Relation::selectIV(int index1, std::string value) {
    Relation newRelation(name, header);
    for (Tuple t : tuples) {
        if (t.getString(index1) == value){
            newRelation.addTuple(t);
        }
    }
    return newRelation;
}

Relation Relation::selectII(int index1, int index2) {
    Relation newRelation(name, header);
    for (Tuple t : tuples) {
        if (t.getString(index1) == t.getString(index2)){
            newRelation.addTuple(t);
        }
    }
    return newRelation;
}

Relation Relation::project(std::vector<int> attributes){
    Header newHeader;
    for (unsigned int i = 0; i < attributes.size(); ++i){
        newHeader.addAttribute(header.getAttribute(attributes.at(i)));
    }
    std::set<Tuple> new_rows;
    for (Tuple t : tuples) {
        Tuple new_row;
        for (unsigned int i = 0; i < attributes.size(); ++i){
            new_row.addString(t.getString(attributes.at(i)));
        }
        new_rows.insert(new_row);
    }
    Relation newRelation(name, newHeader);
    for (Tuple t : new_rows){
        newRelation.addTuple(t);
    }
    return newRelation;
}

/*Relation Relation::project(std::vector<int> attributes){
    std::vector<Tuple> tempTuples;

    // for each tuple, save tuple and



    for (unsigned int i = 0; i < header.getAttributeVector().size(); ++i){
        Tuple tempTuple;
        for (Tuple t : tuples) {
            for (unsigned int j = 0; j < attributes.size(); ++j){
                if (i == j){
                    //if (header.getAttribute(i) == attributes.at(j)){
                    tempTuple.addString(t.getString(i));
                }
            }
        }
        if (tempTuple.getStrings().size() > 0) tempTuples.push_back(tempTuple);
    }
    Relation newRelation(name, header);
    for (unsigned int i = 0; i < tempTuples.size(); ++i){
        newRelation.addTuple(tempTuples.at(i));
    }
    return newRelation;
}*/

Relation Relation::rename(std::vector<std::string> replacers){
    Header tempHeader = header;
    for (unsigned int i = 0; i < replacers.size(); ++i){
        tempHeader.setAttribute(i, replacers.at(i));
    }
    Relation newRelation(name, tempHeader);
    newRelation.addTuples(tuples);
    return newRelation;
}

std::string Relation::toString() {
    std::stringstream ss;
    if (tuples.size() > 0) ss << "Yes(" << tuples.size() << ")";
    else ss << "No";
    for (Tuple t : tuples) {
        if (header.getAttributeVector().size() > 0) ss << std::endl << "  ";
        for (unsigned int i = 0; i < t.getStrings().size(); ++i){
            ss << header.getAttribute(i) << " =" << t.getString(i);
            if (i < t.getStrings().size() - 1) ss << " ,";

        }

    }
    return ss.str();
}
