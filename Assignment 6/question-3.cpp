// O(V+E) + O(V+E) + O(V+E) ~ O(V+E) , where V = no. of vertices, E = no. of edges. The first step is a simple DFS, so the first term is O(V+E). The second step of reversing the graph and the third step, containing DFS again, will take O(V+E) each.

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution
{
private:
    void DFS(int node, vector<int> &visited, vector<int> adj[],
             stack<int> &st)
    {
        visited[node] = 1;
        for (auto neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                DFS(neighbor, visited, adj, st);
            }
        }

        st.push(node);
    }

private:
    void DFS2(int node, vector<int> &visited, vector<int> adjT[])
    {
        visited[node] = 1;
        for (auto neighbor : adjT[node])
        {
            if (!visited[neighbor])
            {
                DFS2(neighbor, visited, adjT);
            }
        }
    }

public:
    // Function to find number of strongly connected components in the graph.
    int kosaraju(int numVertices, vector<int> adj[])
    {
        vector<int> visited(numVertices, 0);
        stack<int> st;
        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                DFS(i, visited, adj, st);
            }
        }

        vector<int> adjT[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = 0;
            for (auto neighbor : adj[i])
            {
                adjT[neighbor].push_back(i);
            }
        }
        int scc = 0;
        while (!st.empty())
        {
            int node = st.top();
            st.pop();
            if (!visited[node])
            {
                scc++;
                DFS2(node, visited, adjT);
            }
        }
        return scc;
    }
};

int main()
{

    int numVertices = 5;
    int edges[5][2] = {
        {1, 0}, {0, 2}, {2, 1}, {0, 3}, {3, 4}};
    vector<int> adj[numVertices];
    for (int i = 0; i < numVertices; i++)
    {
        adj[edges[i][0]].push_back(edges[i][1]);
    }
    Solution obj;
    int ans = obj.kosaraju(numVertices, adj);
    cout << "The number of strongly connected components is: " << ans << endl;
    return 0;
}