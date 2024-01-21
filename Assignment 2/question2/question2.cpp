#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void merge(vector<int> arr, int start, int mid, int end)
{
    int start2 = mid + 1;

    if (arr[mid] <= arr[start2])
    {
        return;
    }

    while (start <= mid && start2 <= end)
    {
        if (arr[start] <= arr[start2])
        {
            start++;
        }
        else
        {
            int value = arr[start2];
            int index = start2;

            while (index != start)
            {
                arr[index] = arr[index - 1];
                index--;
            }

            arr[start] = value;

            start++;
            mid++;
            start2++;
        }
    }
}

void mergeSort(vector<int> arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    ifstream myFile("input.txt");
    int n;

    if (!myFile.is_open())
    {
        cerr << "Error opening the file!" << endl;
        return 1;
    }

    myFile >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
        myFile >> arr[i];

    myFile.close();

    mergeSort(arr, 0, n - 1);

    ofstream outFile("output.txt");

    for (auto i : arr)
    {
        outFile << i << " ";
    }

    outFile.close();

    return 0;
}
