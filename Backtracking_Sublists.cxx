// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void SublistHelper(vector<string>& inputVec, vector<string>& chosen)
{
    if(inputVec.empty())
    {
        for(auto name : chosen)
            cout << name << " ";
        cout << endl;
    }
    else
    {
        string first = inputVec[0];
        inputVec.erase(inputVec.begin());

        // Explore with first name
        chosen.push_back(first);
        SublistHelper(inputVec, chosen);

        // Explore without first name
        chosen.pop_back();
        SublistHelper(inputVec, chosen);

        // Backtrack
        inputVec.insert(inputVec.begin(), first);
    }
    
}

void Sublist(vector<string>& inputVec)
{
    vector<string> chosen;
    SublistHelper(inputVec, chosen);
}

int main()
{
    vector<string> inputVec = {"Jane", "Bob", "Matt", "Sara"};
    Sublist(inputVec);
}