// Source: CIT 594 Programming Languages & Techniques II
// https://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

static const char WhiteMarble = 'W';
static const char BlackMarble = 'B';
static const char EmptySpace = '_';

class CindyPuzzleBoard
{
public:
    CindyPuzzleBoard()
    {
        vec = {BlackMarble, BlackMarble, BlackMarble, EmptySpace, WhiteMarble, WhiteMarble, WhiteMarble};
        emptyCellIndex = 3;
    }

    int GetEmptyCellIndex(){return emptyCellIndex;}

    int GetSize(){return vec.size();}

    bool CanMove(int index)
    {
        if(index == emptyCellIndex || index < 0 || index >= vec.size())
            return false;

        char c = vec[index];

        // The black marbles can only move to the right
        // The white marbles can only move to the left

        // Move one space ahead, if that space is clear
        if((c == BlackMarble && (emptyCellIndex - index == 1)) ||
            (c == WhiteMarble && (index - emptyCellIndex == 1)))
            return true;

        // Jump ahead over exactly one marble of the opposite color, if the space just beyond that marble is clear.
        if((c == BlackMarble && (emptyCellIndex - index == 2) && vec[index+1] == WhiteMarble) ||
            (c == WhiteMarble && (index - emptyCellIndex == 2) && vec[index-1] == BlackMarble))
            return true;

        return false;
    }

    void Move(int index)
    {
        vec[emptyCellIndex] = vec[index];
        vec[index] = EmptySpace;
        emptyCellIndex = index;
    }

    bool IsSolved()
    {
        return(vec == vector<char>{WhiteMarble, WhiteMarble, WhiteMarble, EmptySpace, BlackMarble, BlackMarble, BlackMarble});
    }

    string GetStringForPrint()
    {
        string str;
        for(auto c:vec)
            str = str + c + " ";
        return str;
    }

private:
    vector<char> vec;
    int emptyCellIndex;
};

bool Solve(CindyPuzzleBoard& board, int index = 2, int step = 1)
{
    // Choose
    string str = board.GetStringForPrint();
    int emptyCellIndex = board.GetEmptyCellIndex();
    board.Move(index);        

    if(board.IsSolved())
    {
        cout << setw(2) << step+1 << ". " << board.GetStringForPrint() << endl;            
        cout << setw(2) << step << ". " << str << endl; 
        return true;
    }

    // Explore
    for(int i=0; i<board.GetSize(); ++i)
    {
        // Remove current move from candidate list
        if(i != index && i != emptyCellIndex)
        {
            if(board.CanMove(i))
            {
                if(Solve(board, i, step+1))
                {   
                    cout << setw(2) << step << ". " << str << endl;
                    return true;
                }
            }
        }
    }

    // Backtrack
    board.Move(emptyCellIndex);
    
    return false;
}

int main()
{
    CindyPuzzleBoard board;
    Solve(board);
}