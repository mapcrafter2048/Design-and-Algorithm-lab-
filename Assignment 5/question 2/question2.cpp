#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int minDiceThrows(vector<int> &board, int N)
{
    queue<pair<int, int>> q;
    vector<bool> visited(N + 1, false);

    q.push({1, 0});
    visited[1] = true;

    while (!q.empty())
    {
        int cell = q.front().first;
        int distance = q.front().second;
        q.pop();

        if (cell == N)
        {
            return distance;
        }

        for (int i = 1; i <= 6; i++)
        {
            int nextCell = cell + i;

            if (nextCell <= N && !visited[nextCell])
            {
                visited[nextCell] = true;

                if (board[nextCell] != -1)
                {
                    nextCell = board[nextCell];
                }

                q.push({nextCell, distance + 1});
            }
        }
    }

    return -1;
}

int main()
{
    int N = 30;

    vector<int> board(N + 1, -1);

    board[3] = 22;
    board[5] = 8;
    board[11] = 26;
    board[20] = 29;
    board[17] = 4;
    board[19] = 7;
    board[27] = 1;

    int minThrows = minDiceThrows(board, N);

    if (minThrows != -1)
    {
        cout << "Minimum number of dice throws required: " << minThrows << endl;
    }
    else
    {
        cout << "Destination cell is not reachable." << endl;
    }

    return 0;
}
