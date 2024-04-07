#include <bits/stdc++.h>
using namespace std;

int parent[100005];

vector<int> present;

int edg;

struct edge
{
    int src, dest, weight;
} edges[100005];

bool cmp(edge x, edge y)
{
    return x.weight < y.weight;
}

void initialise(int n)
{
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

int find(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

int union1(int i, int sum)
{
    int x, y;
    x = find(edges[i].src);
    y = find(edges[i].dest);
    if (x != y)
    {
        parent[x] = y;

        present.push_back(i);

        sum += edges[i].weight;
    }
    return sum;
}

int union2(int i, int sum)
{
    int x, y;
    x = find(edges[i].src);
    y = find(edges[i].dest);
    if (x != y)
    {
        parent[x] = y;

        sum += edges[i].weight;
        edg++;
    }
    return sum;
}

int main()
{
    int V, E;
    V = 5;
    E = 8;

    initialise(V);

    vector<int> source = {1, 3, 2, 3,
                          2, 5, 1, 3};
    vector<int> destination = {3, 4, 4,
                               2, 5, 4, 2, 5};
    vector<int> weights = {75, 51, 19,
                           95, 42, 31, 9, 66};
    for (int i = 0; i < E; i++)
    {
        edges[i].src = source[i];
        edges[i].dest = destination[i];
        edges[i].weight = weights[i];
    }

    sort(edges, edges + E, cmp);

    int sum = 0;
    for (int i = 0; i < E; i++)
    {
        sum = union1(i, sum);
    }

    cout << "MST: " << sum << "\n";

    int sec_best_mst = INT_MAX;

    sum = 0;
    int j;
    for (j = 0; j < present.size(); j++)
    {
        initialise(V);
        edg = 0;
        for (int i = 0; i < E; i++)
        {

            if (i == present[j])
                continue;
            sum = union2(i, sum);
        }

        if (edg != V - 1)
        {
            sum = 0;
            continue;
        }

        if (sec_best_mst > sum)
            sec_best_mst = sum;
        sum = 0;
    }

    cout << "Second Best MST: "
         << sec_best_mst << "\n";
    return 0;
}