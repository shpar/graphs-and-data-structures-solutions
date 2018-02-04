#include "2sum.h"

SUMCompute::SUMCompute (unsigned int numbers) : numbers(numbers)
{
    inputNumbers.reserve(numbers);
};

// read input data from file
void SUMCompute::buildFromFile(string file)
{
    ifstream fileStream{file};
    if (!fileStream)
    {
        cout << "File could not be opened" << endl;
        return;
    }
    else
    {
        long i;
        string line;
        while (getline(fileStream, line, '\n'))
        {
            istringstream istr(line);
            istr >> i;
            if (inputNumbers.count(i) == 0)
            {
                inputNumbers.insert({i, 0});
            }
        }
    }
}

// returns true if it finds a distinct pair of numbers x and y from the inputNumbers
// hash table, for which it holds that x + y = desiredSum
bool SUMCompute::findPairs(long desiredSum)
{
    for (const auto& key: inputNumbers)
    {
        if (inputNumbers.count(desiredSum - key.first) > 0 && (key.first * 2 != desiredSum))
        {
            return true;
        }
    }
    return false;
}

bool SUMCompute::findPairs2(long desiredSum)
{

    for (const auto& key: inputNumbers)
    {
        unordered_map<long, char>::const_iterator it = inputNumbers.find(desiredSum - key.first);
        if (it != inputNumbers.end() && (key.first * 2 != desiredSum))
        {
            return true;
        }
    }
    return false;
}

// returns number of sums from interval [minSum, maxSum] for each of which there
// exist at least two distinct numbers x, y in the input, where x + y = particularSum
unsigned int SUMCompute::numSums(long minSum, long maxSum)
{
    assert(minSum < maxSum);
    unsigned int numSums = 0;
    for (long i = minSum; i <= maxSum; i++)
    {
        if (findPairs2(i))
        {
            numSums++;
        }
    }
    return numSums;
}

int main()
{
    SUMCompute Test(1e6);
    Test.buildFromFile("algo1-programming_prob-2sum.txt");
    unsigned int result = Test.numSums(-10000, 10000);
    cout << result << endl;
}
