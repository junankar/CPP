// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>

using namespace std;

void DiceRollHelper(int diceIndex, vector<int>& combination)
{
    cout << "Dice Index:" << diceIndex << endl;
    for(auto i:combination)
        cout << i << " ";
    cout << endl;

    // Base Case
    if(diceIndex == 0)
    {
        /*
        for(auto i:combination)
            cout << i << " ";
        cout << endl;
        */
    }
    else
    {
        // Current dice can contribute to 1-6 values
        for(int i=1; i<=6; ++i)
        {
            // Choose one value for current die
            combination.push_back(i);

            // Explore next dice
            DiceRollHelper(diceIndex-1, combination);

            // Backtrack
            combination.pop_back();
        }
    }
}

void DiceRoll(int diceCount)
{
    vector<int> combination;
    DiceRollHelper(diceCount, combination);
}

int main()
{
    DiceRoll(2);
}