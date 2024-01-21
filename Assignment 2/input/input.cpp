#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateInputFile(const string &filename, int size)
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        cerr << "Error opening output file." << endl;
        return;
    }

    // Write the array size to the file
    outputFile << size << endl;

    // Generate and write random array elements to the file
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < size; ++i)
    {
        outputFile << rand() % 1000000 + 1 << endl; // Generating random integers for demonstration
    }

    outputFile.close();
}

int main()
{
    const string inputFilename = "input.txt";
    const int arraySize = 1000; // Change this to the desired array size

    generateInputFile(inputFilename, arraySize);

    cout << "Generated input file: " << inputFilename << endl;

    return 0;
}
