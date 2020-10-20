// Source: 14 CS 106B Lecture Backtracking printBinary, printDecimal
// https://youtu.be/zL4mjpYpRmc
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ChessBoard
{
public:

    ChessBoard(int n):colIndices(n,-1)
    {
    }

    int GetSize()
    {
        return colIndices.size();
    }

    void PlaceQueen(int row, int col)
    {
        colIndices[row] = col;
    }

    void RemoveQueen(int row, int col)
    {
        colIndices[row] = -1;
    }

    bool IsSafeToPlaceQueen(int row, int col)
    {   
        for(int placedRow=0; placedRow<colIndices.size(); ++placedRow)
        {
            int placedCol = colIndices[placedRow];
            if(placedCol == -1)
                continue;
            
            // Check if same row/ column already has got queen
            if(placedRow == row || placedCol == col)
                return false;
            
            // Check if these two queens are placed on diagonal
            if(abs(placedRow - row) == abs(placedCol - col))
                return false;
        }

        return true;
    }

    void Print()
    {
        for(int row=0; row<colIndices.size(); ++row)
        {
            for(int col=0; col<colIndices.size(); ++col)
                cout << ((col == colIndices[row]) ? "Q" : "_") << " ";
            cout << endl;
        }
    }

private:

    ChessBoard(){};

    // Represents column index for each row where queen is placed
    vector<int> colIndices;
};

bool PlaceQueensHelper(ChessBoard& chessBoard, int row)
{
    if(row == chessBoard.GetSize())
    {
        chessBoard.Print();
        return true;
    }
    else
    {
        for(int col=0; col<chessBoard.GetSize(); ++col)
        {
            if(!chessBoard.IsSafeToPlaceQueen(row, col))
                continue;

            // Choose a column to place queen
            chessBoard.PlaceQueen(row, col);

            // Explore
            if(PlaceQueensHelper(chessBoard, row + 1))
                return true;
            
            // Backtrack
            chessBoard.RemoveQueen(row, col);
        }
    }

    return false;
}

void PlaceQueens(int n)
{
    ChessBoard chessBoard(n);
    PlaceQueensHelper(chessBoard, 0);
}

int main()
{
    PlaceQueens(4);
}