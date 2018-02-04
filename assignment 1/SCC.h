#if !defined(SCC_H)
#define SCC_H

#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <cassert>
#include <deque>

using namespace std;

class Graph
{
public:
    Graph (int nodes);
    ~Graph (){};
    void addNode(unsigned int tail, unsigned int head);
    void buildFromFile(string file, unsigned int nodes);
    void DFS_1(unsigned int startNode, const vector<vector<unsigned int> >& inputVector);
    void DFS_2(unsigned int startNode, const vector<vector<unsigned int> >& inputVector);
    void DFS_over_nodes_1(const vector<vector<unsigned int> >& inputVector);
    void DFS_over_nodes_2(const vector<vector<unsigned int> >& inputVector);
    void DFS_non_recursive(unsigned int startNode, const vector<vector<unsigned int> >& inputVector, bool flag);
    void kosaraju(string filePath, unsigned int nodes);
    
    vector<vector<unsigned int> > edges;
    vector<vector<unsigned int> > reverseEdges;
    vector<bool> discovered;
    deque<unsigned int> maxSCC;
    vector<unsigned int> finishingTimes;
    vector<unsigned int> childsVisited;

    unsigned int finishingTime;
    unsigned int sizeCounter;
    unsigned int currentMax;
private:
    unsigned int nodes;
};

#endif
