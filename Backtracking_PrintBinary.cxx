// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>

using namespace std;

void PrintBinary(int digits, string prefix = "")
{
    if(digits == 0)
    {
        // Base case
        cout << prefix << endl;
    }
    else
    {
        // Recursive case
        // Reducing factor = -1
        // Contribution: "0", "1"
        PrintBinary (digits - 1, prefix + "0");
        PrintBinary (digits - 1, prefix + "1");
    }
}

int main()
{
    PrintBinary(2);
}