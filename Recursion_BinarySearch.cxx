// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>

using namespace std;

int BinarySearch(const vector<int>& vec, int intToSearch, int leftIndex, int rightIndex)
{
    if((rightIndex - leftIndex) <= 0)
    {
        // Base case
        return -1;
    }
    else
    {
        // Recursive case
        // Contribution: compare leftIndex, rightIndex
        // Reducing factor = -1
        if(vec[leftIndex] == intToSearch)
            return leftIndex;

        if(vec[rightIndex] == intToSearch)
            return rightIndex;

        int mid = (leftIndex + rightIndex) / 2;
        if(mid == rightIndex || mid == leftIndex)
            return -1;

        if(intToSearch == vec[mid])
        {
            return mid;
        }
        else if(intToSearch > vec[mid])
        {
            return BinarySearch(vec, intToSearch, mid+1, rightIndex);
        }
        else
        {
            return BinarySearch(vec, intToSearch, leftIndex, mid-1);
        }        
    }
}

int main()
{
    vector<int> vec{1, 2, 5, 8, 10, 11, 13, 15};
    cout << BinarySearch(vec, 13, 0, vec.size() - 1);
}