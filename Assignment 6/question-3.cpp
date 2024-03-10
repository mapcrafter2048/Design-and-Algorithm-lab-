#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Graph
{
    int V;
    vector<int> *adj;
    void SCCUtil(int u, vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &stackMember, vector<vector<int>> &result);

public:
    Graph(int V);
    void addEdge(int u, int v);
    vector<vector<int>> findSCC();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::SCCUtil(int u, vector<int> &disc, vector<int> &low, stack<int> &st, vector<bool> &stackMember, vector<vector<int>> &result)
{
    static int time = 0;
    disc[u] = low[u] = ++time;
    st.push(u);
    stackMember[u] = true;

    for (int v : adj[u])
    {
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember, result);
            low[u] = min(low[u], low[v]);
        }
        else if (stackMember[v])
        {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u])
    {
        vector<int> component;
        while (st.top() != u)
        {
            int v = st.top();
            st.pop();
            stackMember[v] = false;
            component.push_back(v);
        }
        int v = st.top();
        st.pop();
        stackMember[v] = false;
        component.push_back(v);
        result.push_back(component);
    }
}

vector<vector<int>> Graph::findSCC()
{
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<bool> stackMember(V, false);
    stack<int> st;
    vector<vector<int>> result;

    for (int i = 0; i < V; i++)
    {
        if (disc[i] == -1)
        {
            SCCUtil(i, disc, low, st, stackMember, result);
        }
    }

    return result;
}

int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph g(V);

    cout << "Enter the edges (source and destination):" << endl;
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    vector<vector<int>> SCCs = g.findSCC();

    cout << "Strongly Connected Components:" << endl;
    for (const auto &component : SCCs)
    {
        for (int v : component)
        {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}