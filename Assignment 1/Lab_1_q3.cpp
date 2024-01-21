#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int calculateCost(const vector<vector<int>> &distances, const vector<int> &permutation)
{
    int cost = 0;
    int n = permutation.size();

    for (int i = 0; i < n - 1; i++)
    {
        int city1 = permutation[i];
        int city2 = permutation[i + 1];
        cost += distances[city1][city2];
    }

    // Add cost to return to the original city
    int lastCity = permutation[n - 1];
    int firstCity = permutation[0];
    cost += distances[lastCity][firstCity];

    return cost;
}

int main()
{
    // Define the distances between cities
    vector<vector<int>> distances = {
        {0, 20, 42, 35},
        {20, 0, 30, 34},
        {42, 30, 0, 12},
        {35, 34, 12, 0}};

    // Generate all possible permutations of cities
    vector<int> cities = {0, 1, 2, 3}; // Assuming 4 cities
    int minCost = INF;
    vector<int> shortestRoute;

    do
    {
        int cost = calculateCost(distances, cities);

        if (cost < minCost)
        {
            minCost = cost;
            shortestRoute = cities;
        }
    } while (next_permutation(cities.begin(), cities.end()));

    // Print the shortest route and its cost
    cout << "Shortest Route: ";
    for (int city : shortestRoute)
    {
        cout << city << " ";
    }
    cout << shortestRoute[0] << endl;

    cout << "Cost: " << minCost << endl;

    return 0;
}
