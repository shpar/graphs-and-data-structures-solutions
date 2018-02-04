#include "shortest_path.h"

Graph::Graph (int nodes) : currentNode(0), currentShortestPath(0), nodes(nodes)
{
    edges.reserve(nodes);
    weights.reserve(nodes);
    vertices.resize(nodes);
    visited.resize(nodes, false);
    visitedVertices.reserve(nodes);
    // initialize shortest paths to 1e6, which represents no path to given node
    // as per problem instruction
    shortestDistance.resize(nodes, 1e6);
};

// read input data from file
void Graph::buildFromFile(string file, unsigned int nodes)
{
    ifstream fileStream{file};
    if (!fileStream)
    {
        cout << "File could not be opened" << endl;
        return;
    }
    else
    {
        unsigned int i, j, k;
        string line;
        while (getline(fileStream, line, '\n'))
        {
            istringstream istr(line);
            istr >> k;
            while (istr >> i)
            {
                istr.ignore(256, ',');
                istr >> j;
                edges.push_back(i - 1);
                weights.push_back(j);
                vertices[k - 1].push_back(edges.size() - 1);
            }
        }
    }
}

// finds next node from input set X (visitedVertices) according to the greedy
// criterion (shortest path) and returns true if found. The selected node and
// the shortest path to it are saved in currentNode and currentShortestPath
bool Graph::shortestOneStep()
{
    bool notAllDiscovered = false;
    bool verticeHasChilds = false;
    unsigned int tailNode, edgeId, headNode;
    currentShortestPath = numeric_limits<unsigned int>::max();
    // iterate over all vertices in set X (all visited vertices)
    for (unsigned int k = 0; k < visitedVertices.size(); k++)
    {
        tailNode = visitedVertices[k];
        // iterate over all edges of given vertice
        for (unsigned int i = 0; i < vertices[tailNode].size(); i++)
        {
            edgeId = vertices[tailNode][i];
            headNode = edges[edgeId];
            // if the edge points to an undiscovered node, check its greedy criterion
            // that is, the shortest path to tail node plus the weight of given edge
            if (!visited[headNode])
            {
                verticeHasChilds = true;
                if ((shortestDistance[tailNode] + weights[edgeId]) < currentShortestPath)
                {
                    notAllDiscovered = true;
                    currentShortestPath = shortestDistance[tailNode] + weights[edgeId];
                    currentNode = headNode;
                }
            }
        }
        // remove vertice that has no undiscovered childs to optimize performance
        if (!verticeHasChilds)
        {
            visitedVertices.erase(visitedVertices.begin() + k);
        }
    }
    return notAllDiscovered;
}

// computes shortest paths from input startNode to all other connected nodes
// using Dijkstra's algorithm (paths saved in shortestDistance vector)
void Graph::primitiveDijkstra(unsigned int startNode)
{
    shortestDistance[startNode] = 0;
    currentNode = startNode;
    visited[currentNode] = true;
    visitedVertices.push_back(currentNode);
    while (shortestOneStep())
    {
        visited[currentNode] = true;
        visitedVertices.push_back(currentNode);
        shortestDistance[currentNode] = currentShortestPath;
    }
}

int main()
{
    Graph Test(200);
    Test.buildFromFile("dijkstraData.txt", 200);
    Test.primitiveDijkstra(0);
    cout << "Shortest distances from first node:" << endl;
    for (int i = 0; i < 200; i++)
    {
        cout << "#" << (i + 1) << ": "
             << Test.shortestDistance[i] << endl;
    }
}

