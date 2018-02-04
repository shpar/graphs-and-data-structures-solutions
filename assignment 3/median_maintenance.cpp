#include "median_maintenance.h"

MedianCompute::MedianCompute (unsigned int numbers) : numbers(numbers)
{
    inputNumbers.reserve(numbers);
    medians.reserve(numbers);
};

// read input data from file
void MedianCompute::buildFromFile(string file, unsigned int numbers)
{
    ifstream fileStream{file};
    if (!fileStream)
    {
        cout << "File could not be opened" << endl;
        return;
    }
    else
    {
        unsigned int i;
        string line;
        while (getline(fileStream, line, '\n'))
        {
            istringstream istr(line);
            istr >> i;
            inputNumbers.push_back(i);
        }
    }
}

// move top element from heap that has two elements more than the other
void MedianCompute::balanceHeaps()
{
    if (highHeap.size() > lowHeap.size() + 1)
    {
        lowHeap.push(highHeap.top());
        highHeap.pop();
    }
    else if (lowHeap.size() > highHeap.size() + 1)
    {
        highHeap.push(lowHeap.top());
        lowHeap.pop();
    }
}

// return median, if heaps are balanced and throw error otherwise
unsigned int MedianCompute::returnMedian()
{
    if (highHeap.size() == lowHeap.size() + 1)
    {
        return highHeap.top();
    }
    else if (lowHeap.size() == highHeap.size() + 1)
    {
        return lowHeap.top();
    }
    else if (highHeap.size() == lowHeap.size())
    {
        return lowHeap.top();
    }
    else
    {
        throw runtime_error("Error: unbalanced heaps.");
    }
}

// compute medians of numbers from inputNumbers vector
// save the median for each iteration of adding another number
// from the data set
void MedianCompute::computeMedians()
{
    lowHeap.push((inputNumbers[1] > inputNumbers[0]) ? inputNumbers[0] : inputNumbers[1]);
    highHeap.push((inputNumbers[1] > inputNumbers[0]) ? inputNumbers[1] : inputNumbers[0]);
    medians.push_back(inputNumbers[0]);
    medians.push_back(lowHeap.top());

    for (int i = 2; i < numbers; i++)
    {
        if (inputNumbers[i] > highHeap.top())
        {
            highHeap.push(inputNumbers[i]);
        }
        else
        {
            lowHeap.push(inputNumbers[i]);
        }
        balanceHeaps();
        medians.push_back(returnMedian());
    }
}

int main()
{
    MedianCompute Test(10000);
    Test.buildFromFile("Median.txt", 10000);
    Test.computeMedians();
    unsigned int medianSum = 0;
    for (auto &x : Test.medians)
    {
        medianSum += x;
    }
    cout << "The sum of the medians is:" << medianSum << endl;
}
