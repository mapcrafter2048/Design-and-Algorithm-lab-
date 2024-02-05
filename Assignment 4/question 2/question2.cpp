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

using namespace std;

int medianOfSortedArray(vector<long long int> array1, vector<long long int> array2)
{
    int size1 = array1.size();
    int size2 = array2.size();

    int total = size1 + size2;
    int half = total / 2;

    int left = 0;
    int right = size1 - 1;

    while (true)
    {
        int i = (left + right) / 2;
        int j = half - i - 2;

        int Aleft = (i >= 0 && i < size1) ? array1[i] : INT_MIN;
        int Aright = (i + 1 >= 0 && i + 1 < size1) ? array1[i + 1] : INT_MAX;
        int Bleft = (j >= 0 && j < size2) ? array2[j] : INT_MIN;
        int Bright = (j + 1 >= 0 && j + 1 < size2) ? array2[j + 1] : INT_MAX;

        if (Aleft <= Bright && Bleft <= Aright)
        {
            if (total % 2)
            {
                return min(Aright, Bright);
            }
            else
            {
                return (max(Aleft, Bleft) + min(Aright, Bright)) / 2;
            }
        }
        else if (Aleft > Bright)
        {
            right = i - 1;
        }
        else
        {
            left = i + 1;
        }
    }
}

int main()
{
    // Example 1
    vector<long long int> arr1 = {1, 3, 5};
    vector<long long int> arr2 = {2, 4, 6};
    int result1 = medianOfSortedArray(arr1, arr2);
    cout << "Median: " << result1 << endl;

    // Example 2
    vector<long long int> arr3 = {10, 20, 30, 40, 50};
    vector<long long int> arr4 = {5, 15, 25, 35, 45};
    int result2 = medianOfSortedArray(arr3, arr4);
    cout << "Median: " << result2 << endl;

    // Example 3
    vector<long long int> arr5 = {1, 2, 3};
    vector<long long int> arr6 = {4, 5, 6, 7, 8};
    int result3 = medianOfSortedArray(arr5, arr6);
    cout << "Median: " << result3 << endl;

    return 0;
}
