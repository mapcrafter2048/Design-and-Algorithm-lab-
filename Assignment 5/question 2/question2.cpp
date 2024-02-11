#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int minThrows(vector<int> &board)
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
                int nextCell = (board[i] == -1) ? i : board[i];
                q.push({nextCell, dist + 1});
            }
        }
    }

    return -1; // No path found
}

int main()
{
    // Snake and ladder board representation
    vector<int> board = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    // Ladders
    board[1] = 38;
    board[4] = 14;
    board[9] = 31;
    board[21] = 42;
    board[28] = 84;
    board[36] = 44;
    board[51] = 67;
    board[71] = 91;
    board[80] = 100;

    // Snakes
    board[16] = 6;
    board[47] = 26;
    board[49] = 11;
    board[56] = 53;
    board[62] = 19;
    board[64] = 60;
    board[87] = 24;
    board[93] = 73;
    board[95] = 75;
    board[98] = 78;

    int minThrowsRequired = minThrows(board);
    cout << "Minimum number of throws required: " << minThrowsRequired << endl;

    return 0;
}
