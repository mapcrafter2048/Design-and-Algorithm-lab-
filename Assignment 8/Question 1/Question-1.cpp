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

/// @brief This function is used to compare the weight of two edges
/// @param A The first edge
/// @param B The second edge
bool compare(vector<int> &A, vector<int> &B)
{
    return A[2] < B[2];
}

/// @brief This function is used to create a set of n elements with parent and rank as 0 for each element.
/// @param parent The parent of each element
/// @param rank The rank of each element
/// @param n The number of elements
void makeSet(vector<int> &parent, vector<int> &rank, int n)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

/// @brief This function is used to find the parent of a node
/// @param parent The parent of each element
/// @param node The node whose parent is to be found
/// @return The parent of the node
int findParent(vector<int> &parent, int node)
{
    if (parent[node] == node)
    {
        return node;
    }

    return parent[node] = findParent(parent, parent[node]);
}

/// @brief This function is used to perform the union operation on two sets u and v with parent and rank as parent and rank respectively.
/// @param u The first set
/// @param v The second set
/// @param parent The parent of each element
/// @param rank The rank of each element
void unionFind(int u, int v, vector<int> &parent, vector<int> &rank)
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v])
    {
        parent[u] = v;
    }
    else if (rank[u] > rank[v])
    {
        parent[v] = u;
    }
    else
    {
        parent[u] = v;
        rank[v]++;
    }
}

/// @brief This function is used to find the minimum spanning tree cost of a graph with n nodes and edges as edges.
/// @param edges The edges of the graph
/// @param n The number of nodes in the graph
/// @return The minimum spanning tree cost of the graph
pair<int, vector<vector<int>>> solve(vector<vector<int>> &edges, int n)
{
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(n), rank(n);
    makeSet(parent, rank, n);

    int maxWeight = 0;
    vector<vector<int>> mstEdges;

    for (int i = 0; i < edges.size(); i++)
    {
        int u = findParent(parent, edges[i][0]);
        int v = findParent(parent, edges[i][1]);
        int wt = edges[i][2];

        if (u != v)
        {
            maxWeight += wt;
            unionFind(u, v, parent, rank);
            mstEdges.push_back(edges[i]);
        }
    }

    return make_pair(maxWeight, mstEdges);
}

int main()
{
    auto start = high_resolution_clock::now();

    int n = 6;                                                                                                 // number of nodes
    vector<vector<int>> edges = {{0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4}, {3, 4, 2}, {4, 5, 6}}; // example edges

    pair<int, vector<vector<int>>> result = solve(edges, n);

    cout << "Minimum Spanning Tree Cost: " << result.first << endl;
    cout << "Minimum Spanning Tree Edges: " << endl;
    for (auto edge : result.second)
    {
        cout << edge[0] << " - " << edge[1] << " : " << edge[2] << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}