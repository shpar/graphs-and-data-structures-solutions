#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

class MedianCompute
{
public:
    MedianCompute (unsigned int numbers);
    ~MedianCompute (){};
    void buildFromFile(string file, unsigned int numbers);
    void balanceHeaps();
    unsigned int returnMedian();
    void computeMedians();

    vector<unsigned int> inputNumbers;
    vector<unsigned int> medians;
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>> highHeap;
    priority_queue<unsigned int, vector<unsigned int>, less<unsigned int>> lowHeap;
private:
    unsigned int numbers;
};
