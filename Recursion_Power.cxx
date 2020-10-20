// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>

using namespace std;

int CalculatePower(int base, int exp)
{
    if(exp == 0)
    {
        // Base case
        return 1;
    }
    else
    {
        // Recursive case
        // Contribution: base *
        // Reducing factor = -1
        return base * CalculatePower(base, exp-1);
    }
}

int main()
{
    cout << CalculatePower(5, 3);
}