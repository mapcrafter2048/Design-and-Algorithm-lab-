#include <iostream>
#include <vector>

using namespace std;

bool isBipartite(vector<vector<int>> &graph, int src, vector<int> &color)
{
    color[src] = 1;

    vector<int> queue;
    queue.push_back(src);

    while (!queue.empty())
    {
        int u = queue.front();
        queue.erase(queue.begin());

        if (graph[u][u] == 1)
            return false;

        for (int v = 0; v < graph.size(); v++)
        {
            if (graph[u][v] && color[v] == -1)
            {
                color[v] = 1 - color[u];
                queue.push_back(v);
            }
            else if (graph[u][v] && color[u] == color[v])
                return false;
        }
    }

    return true;
}

bool canDivideIntoCliques(vector<vector<int>> &graph)
{
    int V = graph.size();
    vector<int> color(V, -1);

    for (int i = 0; i < V; i++)
    {
        if (color[i] == -1)
        {
            if (!isBipartite(graph, i, color))
                return false;
        }
    }

    return true;
}

int main()
{
    vector<vector<int>> graph = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 0},
        {0, 1, 0, 0}};

    if (canDivideIntoCliques(graph))
        cout << "The graph can be divided into two cliques.";
    else
        cout << "The graph cannot be divided into two cliques.";

    return 0;
}
