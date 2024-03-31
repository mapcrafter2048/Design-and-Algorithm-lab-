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
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include <random>

using namespace std;
using namespace std::chrono;

string generateKey(int index)
{
    if (index < 26)
    {
        return string(1, 'a' + index); // Single characters for indices under 26
    }
    else
    {
        int firstCharIndex = (index / 26) - 1;
        int secondCharIndex = index % 26;
        return string(1, 'a' + firstCharIndex) + (char)('a' + secondCharIndex);
    }
}

int main()
{
    auto start = high_resolution_clock::now();

    ofstream outfile("input.txt"); // Open the test case file

    int numTestCases;
    int maxJobsPerCase;

    cout << "Enter the number of test cases: ";
    cin >> numTestCases;

    cout << "Enter the maximum number of jobs per test case: ";
    cin >> maxJobsPerCase;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> profitDist(10, 50); // Adjust profit range
    uniform_int_distribution<> deadlineDist(1, 5); // Adjust deadline range

    outfile << numTestCases << endl;

    for (int i = 0; i < numTestCases; ++i)
    {
        int numJobs = rand() % maxJobsPerCase + 1; // Random number of jobs

        vector<pair<string, pair<int, int>>> jobs;
        for (int j = 0; j < numJobs; ++j)
        {
            jobs.push_back(make_pair(generateKey(j), make_pair(deadlineDist(gen), profitDist(gen))));
        }

        // Write the test case to the file
        outfile << numJobs << endl;
        for (auto &job : jobs)
        {
            outfile << job.first << " " << job.second.first << " " << job.second.second << endl;
        }
    }

    outfile.close();
    cout << "Test cases generated in input.txt\n";
    return 0;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}