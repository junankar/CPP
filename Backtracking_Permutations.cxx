// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintPermutationsHelper(const vector<int>& inputVec, vector<int> usedIndices, vector<int>& permutation)
{
    // Base Case
    if(permutation.size() == inputVec.size())
    {
        for(auto number : permutation)
            cout << number << " ";
        cout << endl;
    }
    else
    {
        for(int i=0; i<inputVec.size(); ++i)
        {
            if(std::find(usedIndices.begin(), usedIndices.end(), i) == usedIndices.end())
            {
                // Choose value and contribute
                usedIndices.push_back(i);
                permutation.push_back(inputVec[i]);

                // Explore
                PrintPermutationsHelper(inputVec, usedIndices, permutation);

                // Backtrack
                usedIndices.pop_back();
                permutation.pop_back();
            }
        }
    }    
}

void PrintPermutations(const vector<int>& inputVec)
{
    vector<int> usedIndices;
    vector<int> permutation;
    PrintPermutationsHelper(inputVec, usedIndices, permutation);
}

int main()
{
    vector<int> inputVec = {1,2,3};
    PrintPermutations(inputVec);
}