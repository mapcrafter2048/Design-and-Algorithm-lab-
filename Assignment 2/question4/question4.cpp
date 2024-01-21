#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

int getMedian(vector<int> &arr)
{
    sort(arr.begin(), arr.end());
    int size = arr.size();
    int medianIndex = size / 2;
    if (size % 2 == 0)
    {
        return (arr[medianIndex - 1] + arr[medianIndex]) / 2;
    }
    else
    {
        return arr[medianIndex];
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

    int median = getMedian(arr);

    ofstream outputFile("output.txt");
    if (!outputFile.is_open())
    {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    outputFile << "Median: " << median << endl;

    outputFile.close();

    cout << "Median written to output.txt." << endl;

    return 0;
}
