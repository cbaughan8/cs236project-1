#include "Graph.h"

Graph::Graph(){
    SCCIndex = 0;
}

Graph::Graph(std::vector<Rules *> rules1) {
    this->rules = rules1;
    SCCIndex = 0;
    for (unsigned int i = 0; i < rules.size(); i++){
        std::set<int> emptySet;
        graphMap[i] = emptySet;
        visited.push_back(false);
    }
}

void Graph::addEdge(int node1, int node2) {
    graphMap[node1].insert(node2); // adds node2 to set at node1 in map
}

void Graph::visitEdge(int index) {
    visited[index] = true;
}

std::stack<int> Graph::dfsForestPostorder() {
    for (auto const& node : graphMap){
        if(!visited.at(node.first)){
            dfs(node.first);
        }
    }
    return postorder;
}

std::vector<std::set<int>> Graph::dfsForestSCC(std::vector<int> reversePostorder) {
    for (unsigned int i = 0; i < reversePostorder.size(); i++){
        if (!visited.at(reversePostorder.at(i))){
            std::set<int> emptySet;
            SCCs.push_back(emptySet);
            dfs(reversePostorder.at(i));
            SCCIndex++;
        }
    }
    return SCCs;
}

void Graph::dfs(int node) {
    visited.at(node) = true;
    for (int adjNode : graphMap[node]){
        if(!visited.at(adjNode))
        dfs(adjNode);
    }
    postorder.push(node);
    if (SCCs.size() > 0){
        SCCs.at(SCCIndex).insert(node);
    }
}

std::set<int> Graph::getAdjNodes(int key) {
    return graphMap[key];
}

std::string Graph::SCCToString() {
    std::stringstream ss;
    for (unsigned int i = 0; i < this->SCCs.size(); i++){
        ss << i << ":";
        for (int node: this->SCCs.at(i)){
            ss << node << ",";
        }
        ss << std::endl;
    }
    return ss.str();
}

std::string Graph::dependenciesToString() {
    std::stringstream ss;
    for (auto const& x : graphMap){
        bool commaNeeded = false;
        ss << "R" << x.first << ":";
        for (int y : x.second){
            if (commaNeeded == true) ss << ",";
            ss << "R" << y;
            commaNeeded = true;
        }
        ss << std::endl;
    }
    return ss.str();

}