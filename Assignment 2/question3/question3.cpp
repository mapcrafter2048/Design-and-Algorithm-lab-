#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Function to merge two sorted arrays
void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0, j = 0, k = 0;

    // Merge elements from left[] and right[] into arr[]
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements from left[], if any
    while (i < leftSize)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy remaining elements from right[], if any
    while (j < rightSize)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Function to sort an unsorted array using the merging algorithm
void mergeSort(int arr[], int n)
{
#include <iostream>

    // ...

    if (n <= 1)
    {
        return; // Base case: array is already sorted
    }

    int mid = n / 2;
    int *left = new int[mid];
    int *right = new int[n - mid];

    // Divide the array into two halves
    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < n; i++)
    {
        right[i - mid] = arr[i];
    }

    // Recursively sort the two halves
    mergeSort(left, mid);
    mergeSort(right, n - mid);

    // Merge the sorted halves
    merge(arr, left, mid, right, n - mid);
}

int main()
{
    // Read from input.txt
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

    int *arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        if (!(inputFile >> arr[i]))
        {
            cerr << "Error reading array element from input file." << endl;
            delete[] arr;
            inputFile.close();
            return 1;
        }
    }

    inputFile.close();

    // Sort the array using merge sort
    mergeSort(arr, size);

    // Write to output.txt
    ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        cerr << "Error opening output file." << endl;
        delete[] arr;
        return 1;
    }

    for (int i = 0; i < size; i++)
    {
        outputFile << arr[i] << " ";
    }

    outputFile.close();

    cout << "Sorted array written to output.txt." << endl;

    // Deallocate memory for dynamically allocated array
    delete[] arr;

    return 0;
}
