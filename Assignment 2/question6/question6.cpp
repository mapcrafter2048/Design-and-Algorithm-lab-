#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Function to partition the array and return the pivot index
int partition(vector<int> &arr, int low, int high)
{
    // Choosing the pivot element as the median of the first, middle, and last elements
    int mid = low + (high - low) / 2;
    int pivotIndex = -1;

    if ((arr[low] <= arr[mid] && arr[mid] <= arr[high]) || (arr[high] <= arr[mid] && arr[mid] <= arr[low]))
    {
        pivotIndex = mid;
    }
    else if ((arr[mid] <= arr[low] && arr[low] <= arr[high]) || (arr[high] <= arr[low] && arr[low] <= arr[mid]))
    {
        pivotIndex = low;
    }
    else
    {
        pivotIndex = high;
    }

    int pivot = arr[pivotIndex];
    swap(arr[pivotIndex], arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to perform Quick sort
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int main()
{
    ifstream inputFile("input.txt");
    if (!inputFile.is_open())
    {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int size;
    if (!(inputFile >> size))
    {
        cerr << "Error reading array size from input file." << endl;
        inputFile.close();
        return 1;
    }

    vector<int> arr(size);
    for (int i = 0; i < size; i++)
    {
        if (!(inputFile >> arr[i]))
        {
            cerr << "Error reading array element from input file." << endl;
            inputFile.close();
            return 1;
        }
    }

    inputFile.close();

    quickSort(arr, 0, size - 1);

    ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    for (int i : arr)
    {
        outputFile << i << " ";
    }

    outputFile.close();

    cout << "Sorted array written to output.txt." << endl;

    return 0;
}
