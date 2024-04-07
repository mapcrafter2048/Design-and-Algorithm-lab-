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
#include <tuple>

using namespace std;
using namespace std::chrono;

pair<int, vector<pair<int, int>>> solve(vector<vector<pair<int, pair<int, int>>>> &adj) // <to , <cost , color>>
{
    int n = adj.size();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<bool> visited(n, false);
    vector<pair<int, int>> mstEdges;

    int minCost = 0;
    visited[0] = true;

    for (auto &edge : adj[0])
    {
        pq.push(make_pair(edge.second.first, make_pair(edge.second.second, edge.first)));
    }

    while (!pq.empty())
    {
        int currentCost = pq.top().first;
        int to = pq.top().second.first;
        int color = pq.top().second.second;
        pq.pop();

        if (!visited[to])
        {
            visited[to] = true;
            minCost += currentCost;
            mstEdges.push_back(make_pair(0, to));

            for (auto &edge : adj[to])
            {
                if (edge.second.second != color)
                {
                    pq.push(make_pair(edge.second.first, make_pair(edge.second.second, edge.first)));
                }
            }
        }
    }

    return make_pair(minCost, mstEdges);
}

int main()
{
    auto start = high_resolution_clock::now();

    // Your code here

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}