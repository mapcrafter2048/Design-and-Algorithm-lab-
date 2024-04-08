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
#include <tuple>
#include <utility>

using namespace std;
using namespace std::chrono;

pair<int, vector<pair<int, int>>> findMinAlternatingMST_DP(const vector<vector<tuple<int, int, int>>> &adj)
{
    // number of nodes in the graph
    int n = adj.size();
    // Defining INFINITY to be used as a constant later
    const int INF = INT_MAX / 2;

    // Initalizing a 3D dp table
    vector<vector<vector<int>>> dp(1 << n, vector<vector<int>>(n, vector<int>(2, INF)));
    /*
        % 1 << n Represents all the possible masks with n bits (2^n). Each bit corresponds to a node: 1 means visited and 0 means unvisited
        % n is the node index
        % 2 because of the colour that is 0 for black and 1 for green
        % Each cell dp[mask][j][color] stores the minimum cost to reach node j with the current visited set mask ending with color color. Initially, all are set to INF

    */
    vector<vector<vector<int>>> parent(1 << n, vector<vector<int>>(n, vector<int>(2, -1))); // Store parent node

    // Base case
    dp[1][0][0] = dp[1][0][1] = 0;

    // Recursion
    // iterate through all the mask except the empty mask (all the bits are zero)
    for (int mask = 1; mask < (1 << n); ++mask)
    {
        // iterate through all the nodes
        for (int j = 0; j < n; ++j)
        {
            // if current node j is visited in the current mask
            if (mask & (1 << j))
            {
                // iterate through neighbour {to} of node j with their cost and color
                for (auto &neighbour : adj[j])
                {
                    int to, cost, color;
                    tie(to, cost, color) = neighbour;
                    // if the neighbour {to} is not visted yet and has different color thant the last visited node
                    if (!(mask & (1 << to)) && color != dp[mask][j][1])
                    {
                        //  create a new mask by adding the neighbour bit to the current mask
                        int newMask = mask | (1 << to);
                        // if the current cost to reach neighbour {to} with color is higher than the minimum cost to reach node j with its color plus the edge cost
                        if (dp[newMask][to][color] > dp[mask][j][1] + cost)
                        // update the minimum cost
                        { // Update only if cost reduces
                            dp[newMask][to][color] = dp[mask][j][1] + cost;
                            parent[newMask][to][color] = j;
                        }
                    }
                }
            }
        }
    }

    // Backtrack for edges
    int minCost = INF, finalNode = -1, finalColor = -1;
    for (int i = 0; i < n; ++i)
    {
        for (int color = 0; color < 2; color++)
        {
            if (dp[(1 << n) - 1][i][color] < minCost)
            {
                minCost = dp[(1 << n) - 1][i][color];
                finalNode = i;
                finalColor = color;
            }
        }
    }

    vector<pair<int, int>> mstEdges;
    int curNode = finalNode, curColor = finalColor, curMask = (1 << n) - 1;
    while (curNode != -1)
    {
        int prevNode = parent[curMask][curNode][curColor];
        mstEdges.push_back({prevNode, curNode});
        curMask ^= (1 << curNode); // Remove curNode from mask
        curNode = prevNode;
        curColor ^= 1; // Alternate color
    }

    return make_pair(minCost, mstEdges);
}

int main()
{
    auto start = high_resolution_clock::now();

    vector<vector<tuple<int, int, int>>> adj = {
        {{1, 1, 0}, {2, 2, 1}}, // Node 0: neighbor 1 (cost 1, black), neighbor 2 (cost 2, green)
        {{0, 1, 1}, {2, 3, 0}}, // Node 1: neighbor 0 (cost 1, green), neighbor 2 (cost 3, black)
        {{0, 2, 1}, {1, 3, 0}}  // Node 2: neighbor 0 (cost 2, green), neighbor 1 (cost 3, black)
    };

    auto result = findMinAlternatingMST_DP(adj);
    int minCost = result.first;
    vector<pair<int, int>> mstEdges = result.second;

    cout << "Minimum Cost: " << minCost << endl;
    cout << "MST Edges: " << endl;
    for (auto &edge : mstEdges)
    {
        cout << edge.first << " - " << edge.second << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}