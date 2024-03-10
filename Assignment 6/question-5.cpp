#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> adj;        // Adjacency list representation of the graph
vector<int> low, disc;          // Arrays to store discovery time and low value of each vertex
vector<bool> visited;           // Array to track visited vertices
vector<bool> isArticulation;    // Array to track articulation points
vector<pair<int, int>> bridges; // Vector to store bridges

int time = 0; // Global variable to track discovery time

void dfs(int u, int parent)
{
    int currentTime = 0; // Declare and initialize currentTime
    visited[u] = true;
    disc[u] = low[u] = ++currentTime;
    int children = 0;

    for (int v : adj[u])
    {
        if (!visited[v])
        {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);

            // Check if u is an articulation point
            if (parent != -1 && low[v] >= disc[u])
            {
                isArticulation[u] = true;
            }

            // Check if (u, v) is a bridge
            if (low[v] > disc[u])
            {
                bridges.push_back({u, v});
            }
        }
        else if (v != parent)
        {
            low[u] = min(low[u], disc[v]);
        }
    }

    // Check if u is the root and has more than one child
    if (parent == -1 && children > 1)
    {
        isArticulation[u] = true;
    }
}

void findArticulationPointsAndBridges(int n)
{
    low.resize(n);
    disc.resize(n);
    visited.resize(n);
    isArticulation.resize(n);

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i, -1);
        }
    }

    cout << "Articulation points: ";
    for (int i = 0; i < n; i++)
    {
        if (isArticulation[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;

    cout << "Bridges: ";
    for (auto bridge : bridges)
    {
        cout << "(" << bridge.first << ", " << bridge.second << ") ";
    }
    cout << endl;
}

int main()
{
    int n, m;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;

    adj.resize(n);

    cout << "Enter the edges: " << endl;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    findArticulationPointsAndBridges(n);

    return 0;
}