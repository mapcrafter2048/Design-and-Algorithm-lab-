#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs(int node, vector<int> &visited, vector<vector<int>> &adjList, stack<int> &stk)
{
    vector<int> distances(adjList.size(), -INFINITY);
    visited[node] = 1;
    for (int neighbor : adjList[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, visited, adjList, stk);
        }
        distances[neighbor] = max(distances[neighbor], distances[node] + 1);
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
        int node = stk.top();
        stk.pop();
    }

    return result;
}

pair<vector<int>, vector<int>> longestPath(int numNodes, vector<vector<int>> &adjList, int source)
{
    vector<int> topoOrder = topologicalSort(numNodes, adjList);
    vector<int> distances(numNodes, -INFINITY);
    distances[source] = 0;
    vector<int> parent(numNodes, -1); // Track the parent of each node

    for (int node : topoOrder)
    {
        for (int neighbor : adjList[node])
        {
            if (distances[neighbor] < distances[node] + 1)
            {
                distances[neighbor] = distances[node] + 1;
                parent[neighbor] = node;
            }
        }
    }

    int longestDistance = *max_element(distances.begin(), distances.end());
    int endNode = find(distances.begin(), distances.end(), longestDistance) - distances.begin();

    vector<int> path;
    while (endNode != -1)
    {
        path.push_back(endNode);
        endNode = parent[endNode];
    }
    reverse(path.begin(), path.end());

    return {distances, path};
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
