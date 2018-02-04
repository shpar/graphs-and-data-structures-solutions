#include "SCC.h"

Graph::Graph (int nodes) : finishingTime(0), sizeCounter(1), currentMax(0), nodes(nodes)
{
    edges.resize(nodes);
    reverseEdges.resize(nodes);
    childsVisited.resize(nodes, 0);
    discovered.resize(nodes, false);
    finishingTimes.reserve(nodes);
    maxSCC = {1, 1, 1, 1, 1};
};

void Graph::addNode(unsigned int tail, unsigned int head)
{
    assert(tail > 0);
    assert(head > 0);
    edges[tail - 1].push_back(head - 1);
    reverseEdges[head - 1].push_back(tail - 1);
}

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
        unsigned int i, j;
        string line;
        while (getline(fileStream, line, '\n'))
        {
            istringstream istr(line);
            istr >> i >> j;
            do
            {
                edges[i - 1].push_back(j - 1);
                reverseEdges[j - 1].push_back(i - 1);
            } while (istr >> j);
        }
    }
}

// recursive DFS for calculating finishing times
// startNode in values from 0 to n-1
void Graph::DFS_1(unsigned int startNode, const vector<vector<unsigned int> >& inputVector)
{
    discovered.at(startNode) = true;
    unsigned int size = inputVector.at(startNode).size();
    for (unsigned int i = 0; i < size; ++i)
    {
        if (!discovered[inputVector[startNode][i]])
        {
            DFS_1(inputVector[startNode][i], inputVector);
        }
    }
    // finishingTime initialised to 0
    ++finishingTime;
    finishingTimes.push_back(startNode);
}

// recursive DFS for finding sizes of SCC's (the startNode is the leader of the
// component)
void Graph::DFS_2(unsigned int startNode, const vector<vector<unsigned int> >& inputVector)
{
    if (discovered.at(startNode))
    {
        return;
    }
    discovered.at(startNode) = true;
    unsigned int size = inputVector.at(startNode).size();
    for (unsigned int i = 0; i < size; ++i)
    {
        if (!discovered[inputVector[startNode][i]])
        {
            DFS_2(inputVector[startNode][i], inputVector);
        }
    }
    ++sizeCounter;
}

// iterative implementation of DFS for huge inputs where recursive would overflow
// flag false for calculating finishing times and true for calculating SCC sizes
void Graph::DFS_non_recursive(unsigned int startNode, const vector<vector<unsigned int> >& inputVector, bool flag)
{
    stack<unsigned int> level;
    level.push(startNode);
    discovered[startNode] = true;
    
    bool breakLoop;
    if(flag)
        sizeCounter = 1;
    while(!level.empty())
    {
        breakLoop = false;
        unsigned int currentNode = level.top();
        unsigned int currentNodeSize = inputVector[currentNode].size();
        for (;childsVisited[currentNode] < currentNodeSize; ++childsVisited[currentNode])
        {
            unsigned int i = childsVisited[currentNode];
            unsigned int nextNode = inputVector[currentNode][i];
            if(discovered[nextNode] == false)
            {
                level.push(nextNode);
                discovered[nextNode] = true;
                
                // count the SCC size
                if(flag)
                {
                    sizeCounter++;
                }
                // end of path, jump back one level higher
                breakLoop = true;
                break;
            }
        }
        
        // record the finishing time order of vertices
        if(!flag && !breakLoop)
        {
            finishingTimes.push_back(level.top());
        }
        if(!breakLoop)
        {
            level.pop();
        }
    }
    
    // save SCC size if it's bigger than smallest of (5) currently saved sizes
    if(flag && (sizeCounter > maxSCC[0]))
    {
        maxSCC.push_back(sizeCounter);
        maxSCC.pop_front();
        sort(maxSCC.begin(), maxSCC.end());
    }
}

// DFS loop over nodes for first pass to calculate finishing times
void Graph::DFS_over_nodes_1(const vector<vector<unsigned int> >& inputVector)
{
    assert(nodes == inputVector.size());
    assert(nodes == discovered.size());
    for (unsigned int i = 0; i < nodes; i++)
    {
        if (!discovered[i])
        {
            DFS_non_recursive(i, inputVector, false);
        }
    }
}

// DFS loop over nodes in backward order of finishing times to calculate SCC sizes
void Graph::DFS_over_nodes_2(const vector<vector<unsigned int> >& inputVector)
{

    assert(nodes == inputVector.size());
    assert(nodes == discovered.size());
    unsigned int indexDiscovered = 0;
    for (unsigned int i = 0; i < nodes; i++)
    {
        indexDiscovered = finishingTimes[nodes - i - 1];
        if (!discovered[indexDiscovered])
        {
            // using iterative DFS
            DFS_non_recursive(indexDiscovered, inputVector, true);
            
            // using recursive DFS (not for big input sizes)

            // sizeCounter = 0;
            // DFS_2(indexDiscovered, inputVector);
            // if (sizeCounter > maxSCC[0])
            // {
            //     maxSCC.push_back(sizeCounter);
            //     maxSCC.pop_front();
            //     sort(maxSCC.begin(), maxSCC.end());
            // }
        }
    } 
}

// computes the 5 biggest SCC sizes of given input graph
void Graph::kosaraju(string filePath, unsigned int nodes)
{
    buildFromFile(filePath, nodes);
    DFS_over_nodes_1(this->edges);
    fill(this->discovered.begin(), this->discovered.end(), false);
    fill(this->childsVisited.begin(), this->childsVisited.end(), 0);
    DFS_over_nodes_2(this->reverseEdges);
}

int main()
{
    Graph* InputGraph = new Graph(875714);
    InputGraph->kosaraju("SCC.txt", 875714);
    cout << "Max SCCs:" << endl;
    for (int i = 4; i >= 0; i--)
    {
        cout << InputGraph->maxSCC[i] << endl;
    }
    delete InputGraph;
}
