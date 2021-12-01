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


Relation Relation::rename(std::vector<std::string> replacers){
    Header tempHeader = header;
    for (unsigned int i = 0; i < replacers.size(); ++i){
        tempHeader.setAttribute(i, replacers.at(i));
    }
    Relation newRelation(name, tempHeader);
    newRelation.addTuples(tuples);
    return newRelation;
}

Relation Relation::unionR(Relation relation2) {
    std::set<Tuple> tuples1 = tuples;
    for (Tuple t2 : relation2.getTuples()){
        if(tuples1.insert(t2).second){
            tuples1.insert(t2);
            std::cout << unionedToString(t2);
            /*for (unsigned int i = 0; i < t2.getStrings().size(); i++){
                if (i != 0) std::cout << ", ";
                std::cout << header.getAttribute(0) << "=" << t2.getString(i);
            }
            std::cout << std::endl;*/
        }
    }
    Relation newRelation(name, header);
    for (Tuple t : tuples1){
        newRelation.addTuple(t);
    }
    return newRelation;
}

Relation Relation::join(Relation relation2) {
    std::map<std::string, int> columnPairs;
    std::vector<int> nonMatchingAttributes;
    // Relation newRelation(name, header);
    Header newHeader = combineHeaders(relation2.getHeader(), columnPairs, nonMatchingAttributes);
    // DONE Make a new relation with the combined header (it will start with no tuples in it)
    Relation newRelation(name, newHeader);
    std::set<Tuple> tuples1 = tuples;
    // newRelation.addTuples(tuples);
    // DONE Use a pair of nested for-loops to look at each possible pairing of a tuple from the left and a tuple from the right
    for (Tuple t1 : tuples1){
        for (Tuple t2 : relation2.getTuples()){
            if (isJoinable(t1, t2, columnPairs)){
                Tuple combinedT = combineTuples(t1, t2, nonMatchingAttributes);
                // DONE Put the combined tuple into the new relation (the one made in step 4)
                newRelation.addTuple(combinedT);
                //std::cout << "tuple added in join" << std::endl;
            }
        }
    }
    // DONE Once all pairs of tuples have been checked, return the new relation
    return newRelation;
}

Header Relation::combineHeaders(Header header2, std::map<std::string, int> &columnPairs, std::vector<int> &nonMatchingAttributes) {
    Header header1 = header;
    for (unsigned int j = 0; j < header2.size(); j++){
        bool addAttribute = true;
        for (unsigned int i = 0; i < header1.size(); i++){
            // checks if any attributes from header2 are not in header
            if(header1.getAttribute(i) == header2.getAttribute(j)) addAttribute = false;
        }
        if (addAttribute == true) {
            header1.addAttribute(header2.getAttribute(j));
            nonMatchingAttributes.push_back(j);
        }
        else columnPairs[header2.getAttribute(j)] = j;
    }
    return header1;
    // DONE Calculate which column pairs between the left relation and the right relation need to match values
    // DONE Calculate which columns of the right relation do not have a match in the left relation, and therefore need to be copied (this step is probably best done at the same time as step 1, actually)
    // DONE Make a combined header by copying all of the left header, and the non-matching columns of the right relation (calculated in step 2)
}
bool Relation::isJoinable(Tuple t1, Tuple t2, std::map<std::string, int> columnPairs) {
    // for each attribute in header that has a column pair, if t1 at header.example == t2 at header2.matchingExample
    bool canJoin = true;
    bool pairExists = false;
    for (unsigned int i = 0; i < header.size(); i++){
        // if element exists in column pairs
        if (columnPairs.find(header.getAttribute(i)) != columnPairs.end()){
            pairExists = true;
            if (t1.getString(i) != t2.getString(columnPairs[header.getAttribute(i)])){
                canJoin = false;
            }
        }
    }
    //if (pairExists == false) canJoin = false;
    // DONE Make sure all column pairs that need to match between the two tuples (calculated in step 1) do have matching values.
    // DONE If they don't, then do nothing else with this pair of tuples (do not do step 7 or 8 for this pair).
    return canJoin;
}

Tuple Relation::combineTuples(Tuple t1, Tuple t2, std::vector<int> nonMatchingAttributes) {
    // DONE Assuming step 5 passes and they do match where needed, make a new combined tuple.
    // DONE This is done by copying all of the left tuple, and then copying the non-matching columns of the right tuple (calculated in step 2)
    Tuple combinedT;
    combinedT.setStrings(t1.getStrings());
    for (unsigned int i = 0; i < nonMatchingAttributes.size(); i++){
        combinedT.addString(t2.getString(nonMatchingAttributes.at(i)));
    }
    return combinedT;
}

Header Relation::getHeader(){
    return header;
}

const std::set<Tuple> Relation::getTuples() const {
    return tuples;
}

std::string Relation::toString() {
    std::stringstream ss;
    if (tuples.size() > 0) ss << "Yes(" << tuples.size() << ")";
    else ss << "No";
    for (Tuple t : tuples) {
        if (header.getAttributeVector().size() > 0) ss << std::endl << "  ";
        for (unsigned int i = 0; i < t.getStrings().size(); ++i){
            ss << header.getAttribute(i) << "=" << t.getString(i);
            if (i < t.getStrings().size() - 1) ss << ", ";

        }

    }
    return ss.str();
}

std::string Relation::unionedToString(Tuple t) {
    std::stringstream ss;
    ss << "  ";
    for (unsigned int i = 0; i < t.getStrings().size(); i++){
        if (i != 0) ss << ", ";
        ss << header.getAttribute(i) << "=" << t.getString(i);
    }
    ss << std::endl;
    return ss.str();
}
