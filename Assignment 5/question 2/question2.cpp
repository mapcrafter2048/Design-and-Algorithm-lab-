#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int minThrows(vector<vector<int>> &board)
{
    int n = board.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q;
    q.push({0, 0}); // Starting cell with distance 0
    visited[0] = true;

    while (!q.empty())
    {
        pair<int, int> curr = q.front();
        q.pop();
        int cell = curr.first;
        int dist = curr.second;

        if (cell == n - 1)
        {
            return dist; // Reached the last cell
        }

        for (int i = cell + 1; i <= cell + 6 && i < n; i++)
        {
            if (!visited[i])
            {
                visited[i] = true;
                int nextCell = (board[i / 10][i % 10] == -1) ? i : board[i / 10][i % 10];
                q.push({nextCell, dist + 1});
            }
        }
    }

    return -1; // No path found
}

int main()
{
}
