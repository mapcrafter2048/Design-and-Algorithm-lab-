#include <iostream>
#include <climits>
#include <fstream>

using namespace std;

void findFirstAndSecondMin(int arr[], int size, int &min1, int &min2)
{
    min1 = INT_MAX;
    min2 = INT_MAX;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] < min1)
        {
            min2 = min1;
            min1 = arr[i];
        }
        else if (arr[i] < min2 && arr[i] != min1)
        {
            min2 = arr[i];
        }
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
    inputFile >> size;

    int *arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        inputFile >> arr[i];
    }

    inputFile.close();

    int min1, min2;
    findFirstAndSecondMin(arr, size, min1, min2);

    ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        cerr << "Error opening output file." << endl;
        delete[] arr;
        return 1;
    }

    outputFile << "First Minimum: " << min1 << endl;
    outputFile << "Second Minimum: " << min2 << endl;

    outputFile.close();

    delete[] arr;

    cout << "Outputs written to output.txt." << endl;

    return 0;
}
