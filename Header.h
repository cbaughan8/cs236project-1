#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H
#include <vector>
#include <string>

class Header{
private:
    std::vector<std::string> attributes;
public:
    void addAttribute(std::string attribute);
    std::string getAttribute(int index);
    std::vector<std::string> getAttributeVector();
    void setAttribute(int index, std::string value);
    std::string toString();

};

#endif //PROJECT_1_HEADER_H
