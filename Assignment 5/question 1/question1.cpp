#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<int>> &matrix, int row, int col)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    if (row < 0 || row >= rows || col < 0 || col >= cols || matrix[row][col] != 1)
    {
        return 0;
    }

    matrix[row][col] = 0; // Mark the cell as visited

    int size = 1; // Initialize the size of the region

    // Recursively explore the neighboring cells
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            size += dfs(matrix, row + i, col + j);
        }
    }

    return size;
}

int largestRegionSize(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    int largestSize = 0;

    // Traverse the matrix and find the size of each region
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 1)
            {
                int regionSize = dfs(matrix, i, j);
                largestSize = max(largestSize, regionSize);
            }
        }
    }

    return largestSize;
}

int main()
{
    // Example usage
    vector<vector<int>> matrix = {
        {1, 0, 1, 0, 1},
        {1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1}};

    int largestSize = largestRegionSize(matrix);
    cout << "Size of the largest region: " << largestSize << endl;

    return 0;
}
