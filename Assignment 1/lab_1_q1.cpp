#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findMaxSumOfTwoElements(const : vector<int> &arr)
{
    if (arr.size() < 2)
    {
        throw invalid_argument("Array should have at least 2 elements");
    }

    int maxSum = arr[0] + arr[1];
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            int sum = arr[i] + arr[j];
            maxSum = max(maxSum, sum);
        }
    }

    return maxSum;
}

int main()
{
    vector<int> arr = {3, 1, 4, 6, 8, 2, 5};
    int maxSum = findMaxSumOfTwoElements(arr);
    cout << "Maximum sum of two elements: " << maxSum << endl;

    return 0;
}
