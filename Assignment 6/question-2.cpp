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

using namespace std;

void dfs(int node, vector<int> &visited, vector<vector<int>> &adjList, stack<int> &stk)
{
    visited[node] = 1;
    for (int neighbor : adjList[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, visited, adjList, stk);
        }
    }
    stk.push(node);
}

vector<int> topologicalSort(int numNodes, vector<vector<int>> &adjList)
{
    vector<int> visited(numNodes, 0);
    stack<int> stk;

    for (int i = 0; i < numNodes; i++)
    {
        if (!visited[i])
        {
            dfs(i, visited, adjList, stk);
        }
    }

    vector<int> result;
    while (!stk.empty())
    {
        result.push_back(stk.top());
        stk.pop();
    }

    return result;
}

int longestPath(int numNodes, vector<vector<int>> &adjList, int startNode)
{
    vector<int> topoOrder = topologicalSort(numNodes, adjList);
    vector<int> distances(numNodes, INT_MIN);
    distances[startNode] = 0;

    for (int node : topoOrder)
    {
        for (int neighbor : adjList[node])
        {
            distances[neighbor] = max(distances[neighbor], distances[node] + 1);
        }
    }

    int longestDistance = *max_element(distances.begin(), distances.end());
    return longestDistance;
}

int main()
{
    int numNodes = 6;
    vector<vector<int>> adjList(numNodes);

    adjList[0] = {1, 2};
    adjList[1] = {3};
    adjList[2] = {3, 4};
    adjList[3] = {5};
    adjList[4] = {5};

    int startNode = 0;
    int longestDist = longestPath(numNodes, adjList, startNode);
    cout << "Longest path distance: " << longestDist << endl;

    return 0;
}