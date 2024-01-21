#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<int> mergeArrays(const vector<int> &A, const vector<int> &B)
{
    vector<int> C;
    int i = 0, j = 0;

    while (i < A.size() && j < B.size())
    {
        if (A[i] < B[j])
        {
            C.push_back(A[i]);
            i++;
        }
        else
        {
            C.push_back(B[j]);
            j++;
        }
    }

    while (i < A.size())
    {
        C.push_back(A[i]);
        i++;
    }

    while (j < B.size())
    {
        C.push_back(B[j]);
        j++;
    }

    return C;
}

vector<int> unionArrays(const vector<int> &A, const vector<int> &B)
{
    vector<int> C;
    int i = 0, j = 0;

    while (i < A.size() && j < B.size())
    {
        if (A[i] < B[j])
        {
            C.push_back(A[i]);
            i++;
        }
        else if (A[i] > B[j])
        {
            C.push_back(B[j]);
            j++;
        }
        else
        {
            C.push_back(A[i]);
            i++;
            j++;
        }
    }

    while (i < A.size())
    {
        C.push_back(A[i]);
        i++;
    }

    while (j < B.size())
    {
        C.push_back(B[j]);
        j++;
    }

    return C;
}

vector<int> intersectionArrays(const vector<int> &A, const vector<int> &B)
{
    vector<int> C;
    int i = 0, j = 0;

    while (i < A.size() && j < B.size())
    {
        if (A[i] < B[j])
        {
            i++;
        }
        else if (A[i] > B[j])
        {
            j++;
        }
        else
        {
            C.push_back(A[i]);
            i++;
            j++;
        }
    }

    return C;
}

int main()
{
}
