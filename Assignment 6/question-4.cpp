#include <iostream>
#include <vector>

using namespace std;

bool dfs(vector<vector<int>> &graph, int node, vector<bool> &visited, vector<bool> &recursionStack)
{
    visited[node] = true;
    recursionStack[node] = true; // Mark the current node as part of the recursion stack keeping track of the current path

    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            if (dfs(graph, neighbor, visited, recursionStack))
                return true;
        }
        else if (recursionStack[neighbor])
        {
            return true;
        }
    }

    recursionStack[node] = false;
    return false;
}

bool hasCycle(vector<vector<int>> &graph, int numNodes)
{
    vector<bool> visited(numNodes, false);
    vector<bool> recursionStack(numNodes, false);

    for (int i = 0; i < numNodes; i++)
    {
        if (!visited[i])
        {
            if (dfs(graph, i, visited, recursionStack))
                return true;
        }
    }

    return false;
}

int main()
{
    int numNodes = 5;
    vector<vector<int>> graph(numNodes);

    // Add edges to the graph
    graph[0].push_back(1);
    graph[1].push_back(2);
    graph[2].push_back(0);
    graph[2].push_back(3);
    graph[3].push_back(4);
    graph[4].push_back(2);

    // Call your hasCycle function to test for cycles
    if (hasCycle(graph, numNodes))
    {
        cout << "The graph contains a cycle." << endl;
    }
    else
    {
        cout << "The graph does not contain a cycle." << endl;
    }

    return 0;
}