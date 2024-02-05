#include <iostream>
#include <vector>
using namespace std;

int merge(vector<int> &arr, vector<int> &temp, int left, int mid, int right)
{
    int i = left;
    int j = mid;
    int k = left;
    int invCount = 0;

    while (i <= mid - 1 && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            invCount += (mid - i); // increase the incount by the number of remaining elements in the left subarray (mid - i), as these form inversions with the right element.Since the array is being split and sorted, if arr[i] is greater than arr[j], then arr[i] is also greater than all the elements from arr[i+1] to arr[mid].
        }
    }

    while (i <= mid - 1)
    {
        temp[k++] = arr[i++];
    }

    while (j <= right)
    {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }

    return invCount;
}

int mergeSort(vector<int> &arr, vector<int> &temp, int left, int right)
{
    int invCount = 0;

    if (right > left)
    {
        int mid = (left + right) / 2;

        invCount += mergeSort(arr, temp, left, mid);
        invCount += mergeSort(arr, temp, mid + 1, right);
        invCount += merge(arr, temp, left, mid + 1, right);
    }

    return invCount;
}

int countInversions(vector<int> &arr)
{
    int n = arr.size();
    vector<int> temp(n);
    return mergeSort(arr, temp, 0, n - 1);
}

int main()
{
    vector<int> arr = {3, 2, 1};

    int invCount = countInversions(arr);

    cout << "Total count of inversions: " << invCount << endl;

    return 0;
}