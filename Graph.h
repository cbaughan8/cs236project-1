#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H
#include "Rules.h"

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <stack>

class Graph {
private:
    std::vector<Rules*> rules;
    std::map<int, std::set<int>> graphMap; //the set of ints is the indices of the nodes that int has edges to
    std::vector<bool> visited;
    std::stack<int> postorder;
    std::vector<std::set<int>> SCCs;
    int SCCIndex;
    // SSCs represented by a set of ints

public:
    Graph();
    Graph(std::vector<Rules*> rules1);
    std::stack<int> dfsForestPostorder();
    std::vector<std::set<int>> dfsForestSCC(std::vector<int> reversePostorder);
    void dfs(int node);
    void addEdge(int node1, int node2); // use at the same time to create forward and reverse graph, add node2 to the set
    void visitEdge(int index);
    std::set<int> getAdjNodes(int key);// make visited true in vector
    std::string SCCToString();
    std::string dependenciesToString();



    // use a stack to reverse postorder

};

#endif //PROJECT_1_GRAPH_H
