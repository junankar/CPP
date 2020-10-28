// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc

#include <iostream>
#include <vector>

using namespace std;

int AddValues(const vector<int>& vec, int index=0)
{
    // Base case
    if(index == vec.size())
    {
        return 0;
    }
    else
    {
        // Recursive case
        return vec[index] + AddValues(vec, index+1);
    }
}

int main()
{
    vector<int> vec {1,2,3,4,5,6};
    cout << AddValues(vec);
}