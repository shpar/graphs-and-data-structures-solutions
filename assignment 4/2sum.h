#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <unordered_map>

using namespace std;

class SUMCompute
{
public:
    SUMCompute (unsigned int numbers);
    ~SUMCompute (){};
    void buildFromFile(string file);
    bool findPairs(long desiredSum);
    bool findPairs2(long desiredSum);

    unsigned int numSums(long minSum, long maxSum);

    unordered_map<long, char> inputNumbers;
private:
    unsigned int numbers;
};
