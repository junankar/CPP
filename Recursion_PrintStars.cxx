// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>

using namespace std;

void PrintStars(int count)
{
    if(count == 0)
    {
        // Base case
        // Nothing to do here
    }
    else
    {
        // Recursive case
        // Contribution: "*"
        // Reducing factor = -1
        cout << "*";
        PrintStars(count -1);
    }
}

int main()
{
    PrintStars(10);
}