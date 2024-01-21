#include <iostream>
#include <vector>

using namespace std;

int knapsack(int maxWeight, const vector<int> &weights, const vector<int> &values)
{
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= maxWeight; j++)
        {
            if (weights[i - 1] <= j)
            {
                dp[i][j] = max(values[i - 1] + dp[i - 1][j - weights[i - 1]], dp[i - 1][j]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][maxWeight];
}

int main()
{
    vector<int> weights = {2, 5, 7, 3, 1};
    vector<int> values = {10, 20, 15, 7, 5};
    int maxWeight = 10;

    int maxValue = knapsack(maxWeight, weights, values);
    cout << "Maximum value: " << maxValue << endl;

    return 0;
}
