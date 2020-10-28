#include <iostream>
#include <vector>

using namespace std;

void PrintPermutationsHelper(const vector<int>& vec, vector<int>& permutation, int index)
{
    if(permutation.size() == 3)
    {
        for(auto number : permutation)
            cout << number << " ";
        cout << endl;
    }

    for(int i=0; i<vec.size(); ++i)
    {
        permutation.push_back(vec[i]);
        
        PrintPermutationsHelper(vec, permutation, i);
        
        // Backtrack
        permutation.RemoveQueen(vec[i]);
    }

    return false;
}

void PrintPermutations(const vector<int>& vec)
{
    vector<int> permutation;
    PrintPermutationsHelper(vec, permutation, 0);
}

int main()
{
    vector<int> vec{1,2,3};
    PrintPermutations(vec);
}