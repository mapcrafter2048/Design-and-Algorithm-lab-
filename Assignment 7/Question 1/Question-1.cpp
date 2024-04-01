#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cmath>
#include <climits>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
using namespace std::chrono;

int knapsackDp(vector<long long int> &weights, vector<long long int> &values, long long int weightLimit, int index, vector<vector<long long int>> &dp)
{
    if (weightLimit <= 0 || index >= weights.size())
    {
        return 0;
    }

    // check if the value is already calculated
    auto key = make_pair(weightLimit, index);

    if (dp[index][weightLimit] != -1)
    {
        return dp[index][weightLimit];
    }
    int result = 0;
    if (weights[index] <= weightLimit)
    {
        // taking the current item to the consideration
        result = values[index] + knapsackDp(weights, values, weightLimit - weights[index], index + 1, dp);
    }
    // not taking the current item to the consideration
    result = max(result, knapsackDp(weights, values, weightLimit, index + 1, dp));

    dp[index][weightLimit] = result;
    return result;
}

int knapsackGreedy(vector<long long int> &weights, vector<long long int> &values, long long int weightLimit)
{
    int n = weights.size();
    vector<pair<double, int>> valuePerWeight(n);

    for (int i = 0; i < n; i++)
    {
        valuePerWeight[i] = make_pair((double)values[i] / weights[i], i);
    }

    sort(valuePerWeight.rbegin(), valuePerWeight.rend());

    int totalValue = 0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++)
    {
        int itemIndex = valuePerWeight[i].second;
        if (currentWeight + weights[itemIndex] <= weightLimit)
        {
            totalValue += values[itemIndex];
            currentWeight += weights[itemIndex];
        }
    }

    return totalValue;
}

int main()
{
    auto start = high_resolution_clock::now();
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    int numTestCases;
    inputFile >> numTestCases;

    while (numTestCases--)
    {
        int arraySize;
        inputFile >> arraySize;

        vector<long long int> weights(arraySize);
        vector<long long int> values(arraySize);

        for (int i = 0; i < arraySize; ++i)
        {
            inputFile >> weights[i];
        }

        for (int i = 0; i < arraySize; ++i)
        {
            inputFile >> values[i];
        }

        long long int weightLimit;
        inputFile >> weightLimit;

        vector<vector<long long int>> dp(arraySize, vector<long long int>(weightLimit + 1, -1));

        auto start = high_resolution_clock::now();
        int result = knapsackDp(weights, values, weightLimit, 0, dp);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        outputFile << result << endl;
        outputFile << "Time taken: " << duration.count() << " microseconds" << endl;
    }

    inputFile.close();
    outputFile.close();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    return 0;
}