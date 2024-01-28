#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void merge(vector<int> &arr, int start, int mid, int end)
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

// Function to sort an unsorted array using the merging algorithm
void mergeSort(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;

        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, start, mid, end);
    }
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

    vector<int> arrVec(arr, arr + size);

    mergeSort(arrVec, 0, arrVec.size() - 1);

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
