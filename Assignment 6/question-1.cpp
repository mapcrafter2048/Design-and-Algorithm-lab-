#include <iostream>
#include <vector>
#include <stack>
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

int main()
{
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<int>> adjList(numNodes);

    cout << "Enter the edges:\n";
    for (int i = 0; i < numEdges; i++)
    {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
    }

    vector<int> sortedNodes = topologicalSort(numNodes, adjList);

    cout << "Topological Sort: ";
    for (int node : sortedNodes)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
