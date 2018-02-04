#if !defined(SHORTEST_PATH_H)
#define SHORTEST_PATH_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

class Graph
{
public:
    Graph (int nodes);
    ~Graph (){};
    void buildFromFile(string file, unsigned int nodes);
    void primitiveDijkstra(unsigned int startNode);
    bool shortestOneStep();
    
    vector<vector<unsigned int> > vertices;
    vector<unsigned int> visitedVertices;
    vector<unsigned int> edges;
    vector<unsigned int> weights;
    vector<bool> visited;
    vector<unsigned int> shortestDistance;
    unsigned int currentNode;
    unsigned int currentShortestPath;

private:
    unsigned int nodes;
};

#endif
