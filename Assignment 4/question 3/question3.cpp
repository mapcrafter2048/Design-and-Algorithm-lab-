#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int partition(vector<int> &nums, int low, int high)
{
    int pivot = nums[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (nums[j] <= pivot)
        {
            i++;
            swap(nums[i], nums[j]);
        }
    }
    swap(nums[i + 1], nums[high]);
    return i + 1;
}

int findKthLargest(vector<int> &nums, int k)
{
    int low = 0;
    int high = nums.size() - 1;
    int targetIndex = nums.size() - k;
    while (low <= high)
    {
        int pivotIndex = partition(nums, low, high);
        if (pivotIndex == targetIndex)
        {
            return nums[pivotIndex];
        }
        else if (pivotIndex < targetIndex)
        {
            low = pivotIndex + 1;
        }
        else
        {
            high = pivotIndex - 1;
        }
    }
    return -1; // Kth largest element not found
}

int main()
{
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int k = 2;
    int kthLargest = findKthLargest(nums, k);
    cout << "The " << k << "th largest element is: " << kthLargest << endl;
    return 0;
}