#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

using Edge = tuple<int, int, int>; // weight , start veterx , end vertex

vector<int> parent, ranks;

int findSet(int u)
{
    return parent[u] == u ? u : parent[u] = findSet(parent[u]);
}

void unionSets(int u, int v)
{
    int pu = findSet(u), pv = findSet(v);
    if (ranks[pu] < ranks[pv])
        swap(pu, pv);
    parent[pv] = pu;
    if (ranks[pu] == ranks[pv])
        ranks[pu]++;
}

int kruskalMST(vector<Edge> &edges)
{
    sort(edges.begin(), edges.end());

    parent.assign(edges.size(), 0);
    ranks.assign(edges.size(), 0);
    iota(parent.begin(), parent.end(), 0);

    int mstCost = 0;

    for (auto &edge : edges)
    {
        int cost, u, v;
        tie(cost, u, v) = edge;
        if (findSet(u) != findSet(v))
        {
            mstCost += cost;
            unionSets(u, v);
        }
    }

    return mstCost;
}

// Finds the second-best MST by excluding one edge at a time
int findSecondBestMST(vector<Edge> &edges)
{
    int bestMST = kruskalMST(edges);
    int secondBestMST = std::numeric_limits<int>::max();

    // iterating over all the edges
    for (auto &edge : edges)
    {
        int cost, u, v;
        tie(cost, u, v) = edge;
        // Resetting the parent and rank vectors
        parent.assign(edges.size(), 0);
        ranks.assign(edges.size(), 0);
        // Initializing the parent vector
        iota(parent.begin(), parent.end(), 0);

        int currentMST = 0;
        bool isValidMST = true;

        // iterating over all the edges again
        for (auto &Edges : edges)
        {
            int edgeCost, edgeU, edgeV;
            tie(edgeCost, edgeU, edgeV) = Edges;
            // Excluding the edge
            if (edgeCost != cost || edgeU != u || edgeV != v)
            {
                if (findSet(edgeU) != findSet(edgeV))
                {
                    currentMST += edgeCost;
                    unionSets(edgeU, edgeV);
                }
                else
                {
                    isValidMST = false;
                    break;
                }
            }
        }

        if (isValidMST && currentMST > bestMST)
        {
            secondBestMST = min(secondBestMST, currentMST);
        }
    }

    return secondBestMST == std::numeric_limits<int>::max() ? -1 : secondBestMST;
}

int main()
{
    vector<Edge> edges;

    edges.push_back(make_tuple(1, 0, 1));
    edges.push_back(make_tuple(2, 0, 2));
    edges.push_back(make_tuple(3, 1, 2));
    edges.push_back(make_tuple(4, 1, 3));
    edges.push_back(make_tuple(5, 2, 3));

    int secondBestMST = findSecondBestMST(edges);
    cout << "Second Best MST Cost: " << secondBestMST << endl;

    return 0;
}
