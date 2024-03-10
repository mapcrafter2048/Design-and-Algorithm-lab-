#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cmath>

using namespace std;

class Solution
{
public:
    int timer = 1;
    void dfs(int currentNode, int parentNode, vector<int> &visited, vector<int> adj[], vector<int> &tin, vector<int> &low, vector<vector<int>> &bridges, vector<int> &isArticulation)
    {
        visited[currentNode] = 1;
        tin[currentNode] = low[currentNode] = timer++;
        int childCount = 0;
        for (auto neighbor : adj[currentNode])
        {
            if (neighbor == parentNode)
                continue;
            if (visited[neighbor] == 0)
            {
                dfs(neighbor, currentNode, visited, adj, tin, low, bridges, isArticulation);
                low[currentNode] = min(low[neighbor], low[currentNode]);
                if (low[neighbor] > tin[currentNode])
                {
                    bridges.push_back({neighbor, currentNode});
                }

                if (parentNode != -1 && low[neighbor] >= tin[currentNode])
                {
                    isArticulation[currentNode] = true;
                }
                childCount++;
            }
            else
            {
                low[currentNode] = min(low[currentNode], low[neighbor]);
            }
            if (parentNode == -1 && childCount > 1)
            {
                isArticulation[currentNode] = true;
            }
        }
    }

    vector<vector<int>> findBridges(int numNodes, vector<vector<int>> &connections)
    {
        vector<int> adj[numNodes];
        for (auto connection : connections)
        {
            int u = connection[0], v = connection[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> visited(numNodes, 0);
        vector<int> tin(numNodes);
        vector<int> low(numNodes);
        vector<vector<int>> bridges;
        vector<int> isArticulation(numNodes, false);
        dfs(0, -1, visited, adj, tin, low, bridges, isArticulation);
        return bridges;
    }

    vector<int> findArticulationPoints(int numNodes, vector<vector<int>> &connections)
    {
        vector<int> adj[numNodes];

        for (auto connection : connections)
        {
            int u = connection[0], v = connection[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> visited(numNodes, 0);
        vector<int> tin(numNodes);
        vector<int> low(numNodes);
        vector<vector<int>> bridges;
        vector<int> isArticulation(numNodes, false);

        for (int i = 0; i < numNodes; i++)
        {
            if (!visited[i])
            {
                dfs(i, -1, visited, adj, tin, low, bridges, isArticulation);
            }
        }

        vector<int> articulationPoints;
        for (int i = 0; i < numNodes; i++)
        {
            if (isArticulation[i])
            {
                articulationPoints.push_back(i);
            }
        }

        return articulationPoints;
    }
};

int main()
{

    int numNodes = 4;
    vector<vector<int>> connections = {
        {0, 1}, {1, 2}, {2, 0}, {1, 3}};

    Solution obj;
    vector<vector<int>> bridges = obj.findBridges(numNodes, connections);
    for (auto bridge : bridges)
    {
        cout << "[" << bridge[0] << ", " << bridge[1] << "] " << endl;
    }
    int numNodes1 = 5;
    vector<vector<int>> edges = {
        {0, 1}, {1, 4}, {2, 4}, {2, 3}, {3, 4}};

    Solution obj1;
    vector<int> articulationPoints = obj1.findArticulationPoints(numNodes1, edges);

    // Print articulation points
    cout << "Articulation Points: ";
    for (int node : articulationPoints)
    {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}