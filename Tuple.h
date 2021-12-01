#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H
#include <vector>
#include <string>

class Tuple{
private:
    std::vector<std::string> strings;

public:
    Tuple();
    bool operator< (const Tuple &rhs) const {
        return strings < rhs.strings;
    }
    void addString(std::string value);
    void setStrings(std::vector<std::string> newStrings);
    std::string getString(int index1);
    std::vector<std::string> getStrings();
    size_t size();
    std::string toString();

};

#endif //PROJECT_1_TUPLE_H
