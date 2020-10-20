// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>

using namespace std;

void DiceRollHelper(int diceIndex, vector<int>& combination, int currentSum, int targetSum)
{
    // Base Case
    if(currentSum == targetSum)
    {
        for(auto i:combination)
            cout << i << " ";
        cout << endl;
    }
    else if(diceIndex > 0)
    {
        int maxValueForCurrentDice = targetSum - currentSum - diceIndex + 1;

        // Current dice can contribute to 1-6 values
        // However, it can go upto a maximum value where 
        // each of other dice can atleast contribute 1
        for(int i=1; i<=maxValueForCurrentDice; ++i)
        {
            // Choose one value for current die
            combination.push_back(i);
            currentSum = currentSum + i;

            // Explore next dice
            DiceRollHelper(diceIndex-1, combination, currentSum, targetSum);

            // Backtrack
            combination.pop_back();
            currentSum = currentSum - i;
        }
    }
}

void DiceRoll(int diceCount, int targetSum)
{
    vector<int> combination;
    int currentSum = 0;
    DiceRollHelper(diceCount, combination, currentSum, targetSum);
}

int main()
{
    DiceRoll(3, 9);
}