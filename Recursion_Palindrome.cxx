// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <algorithm>

using namespace std;

bool CheckPalindrome(const string& str, int leftIndex, int rightIndex)
{
    if((rightIndex - leftIndex) <= 1)
    {
        // Base case
        return true;
    }
    else
    {
        // Recursive case
        // Contribution: compare leftIndex, rightIndex
        // Reducing factor = -1
        if(str[leftIndex] != str[rightIndex])
            return false;
        return CheckPalindrome(str, ++leftIndex, --rightIndex);
    }
}

int main()
{
    string str = "rise to vote sir";
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    cout << (CheckPalindrome(str, 0, str.size()-1) ? "Yes" : "No");
}