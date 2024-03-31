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

using namespace std;
using namespace std::chrono;

pair<int, vector<string>> jobScheduling(vector<pair<string, pair<int, int>>> &jobs)
{
    sort(jobs.begin(), jobs.end(), [](const pair<string, pair<int, int>> &a, const pair<string, pair<int, int>> &b)
         { return a.second.second > b.second.second ||
                  (a.second.second == b.second.second && a.second.first < b.second.first); });

    int deadline = 0;
    for (const auto &job : jobs)
    {
        deadline = max(deadline, job.second.first);
    }

    int totalProfit = 0;
    vector<string> sequence;
    vector<bool> slot(deadline, false);

    for (const auto &job : jobs)
    {
        string jobName = job.first;
        int jobDeadline = job.second.first;
        int jobProfit = job.second.second;

        for (int i = jobDeadline - 1; i >= 0; i--)
        {
            if (slot[i] == false)
            {
                slot[i] = true;
                sequence.push_back(jobName);
                totalProfit += jobProfit;
                break;
            }
        }
    }

    return make_pair(totalProfit, sequence);
}

int main()
{
    auto start = high_resolution_clock::now();

    // vector<pair<string, pair<int, int>>> jobs = {
    //     make_pair("a", make_pair(3, 20)),
    //     make_pair("b", make_pair(1, 45)),
    //     make_pair("c", make_pair(2, 15)),
    //     make_pair("d", make_pair(3, 30)),
    //     make_pair("e", make_pair(2, 35)),
    //     make_pair("f", make_pair(1, 10))};

    // vector<pair<string, pair<int, int>>> jobs = {
    //     make_pair("a", make_pair(4, 20)),
    //     make_pair("b", make_pair(1, 10)),
    //     make_pair("c", make_pair(1, 40)),
    //     make_pair("d", make_pair(1, 30))};

    vector<pair<string, pair<int, int>>> jobs = {
        make_pair("a", make_pair(2, 10)),
        make_pair("b", make_pair(2, 25)),
        make_pair("c", make_pair(1, 15)),
        make_pair("d", make_pair(3, 20))};

    vector<pair<string, pair<int, int>>> jobs1 = {
        make_pair("a", make_pair(2, 60)),
        make_pair("b", make_pair(1, 100)),
        make_pair("c", make_pair(3, 20)),
        make_pair("d", make_pair(3, 30)),
        make_pair("e", make_pair(1, 50))};

    pair<int, vector<string>> result = jobScheduling(jobs);
    pair<int, vector<string>> result1 = jobScheduling(jobs1);

    cout << "Total Profit: " << result.first << endl;
    cout << "Job Sequence: ";
    for (string job : result.second)
    {
        cout << job << " ";
    }
    cout << endl;
    cout << "Total Profit: " << result1.first << endl;
    cout << "Job Sequence: ";
    for (string job : result1.second)
    {
        cout << job << " ";
    }
    cout << endl;

    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    int numTestCases;
    inputFile >> numTestCases;

    while (numTestCases--)
    {
        int numJobs;
        inputFile >> numJobs;

        vector<pair<string, pair<int, int>>> jobs;
        for (int i = 0; i < numJobs; ++i)
        {
            string jobName;
            int jobDeadline;
            int jobProfit;

            inputFile >> jobName >> jobDeadline >> jobProfit;
            jobs.push_back(make_pair(jobName, make_pair(jobDeadline, jobProfit)));
        }

        pair<int, vector<string>> result = jobScheduling(jobs);

        outputFile << result.first << endl;
        for (string job : result.second)
        {
            outputFile << job << " ";
        }
        outputFile << endl;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;
    return 0;
}
