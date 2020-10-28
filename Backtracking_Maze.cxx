// Source: CIT 594 Programming Languages & Techniques II
// https://www.cis.upenn.edu/~matuszek/cit594-2012/Pages/backtracking.html

#include <deque>
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>

using namespace std;

class Position
{
public:
    Position(int rowId, int colId):m_rowId(rowId), m_colId(colId){}
    int GetRowId() const {return m_rowId;} 
    int GetColId() const {return m_colId;}
    bool operator == (const Position& other)
    {
        return (other.m_rowId == m_rowId) && (other.m_colId == m_colId);
    }
private:
    int m_rowId;
    int m_colId;
};

class Maze
{
public:
    Maze(int size):m_size(size), hBricks(size*(size+1), false), vBricks(size*(size+1), false)
    {
        // Mark outer walls
        for(int i=1; i<=m_size; ++i)
        {
            AddVBrick(i, 0);
            AddVBrick(i, m_size);
            AddHBrick(i, 0);
            AddHBrick(i, m_size);
        }
    }

    void AddHDoor(int colId, bool placeAtBottom)
    {
        int rowId = placeAtBottom ? 0 : m_size;
        hBricks[GetHBrickIndex(colId, rowId)] = false;
    }

    void AddVDoor(int rowId, bool placeOnLeft)
    {
        int colId = placeOnLeft ? 0 : m_size;
        vBricks[GetVBrickIndex(rowId, colId)] = false;
    }

    /*
        To add vertical brick, specify row ID and left column ID
        e.g. AddVBrick(1, 1), AddVBrick(2, 2)
        2         |   
        1  ___|___ ___
            1   2   3 
    */
    void AddVBrick(int rowId, int leftColId)
    {   
        int i = GetVBrickIndex(rowId, leftColId);
        vBricks[GetVBrickIndex(rowId, leftColId)] = true;
    };

    /*
        To add horizontal brick, specify column and row ID below it
        e.g. AddHBrick(2, 1), AddVBrick(3, 2)
        3          ___      
        2      ___   
        1  ___ ___ ___
            1   2   3 
    */
    void AddHBrick(int colId, int rowIdBelow)
    {   
        hBricks[GetHBrickIndex(colId, rowIdBelow)] = true;
    }

    vector<Position> GetCandidatePositions(const Position& playerPos)
    {
        int rowId = playerPos.GetRowId();
        int colId = playerPos.GetColId();

        vector<Position> candidates;

        // Can player move to left?
        if(colId > 1 && !IsVBrickToLeft(rowId, colId))
            candidates.push_back({rowId, colId-1});

        // Can player move to right?
        if(colId < m_size && !IsVBrickToRight(rowId, colId))
            candidates.push_back({rowId, colId+1});

        // Can player move down?
        if(rowId > 1 && !IsHBrickBelow(rowId, colId))
            candidates.push_back({rowId-1, colId});

        // Can player move up?
        if(rowId < m_size && !IsHBrickAbove(rowId, colId))
            candidates.push_back({rowId+1, colId});

        return candidates;                          
    }

    bool CanUserExit(const Position& playerPos)
    {
        int rowId = playerPos.GetRowId();
        int colId = playerPos.GetColId();

        if ((colId == 1 && !IsVBrickToLeft(rowId, colId)) ||
            (colId == m_size && !IsVBrickToRight(rowId, colId)) ||
            (rowId == 1 && !IsHBrickBelow(rowId, colId)) ||
            (rowId == m_size && !IsHBrickAbove(rowId, colId)))
        {
            return true;
        }
        
        return false;
    }

    void Print(const Position& playerPos)
    {
        // Draw top border for top-most row
        cout << "   ";
        for(int colId=1; colId <= m_size; ++colId)
            cout << (IsHBrickAbove(m_size, colId) ? " ___" : "    ");            
        cout << endl;

        for(int rowId=m_size; rowId >= 0; --rowId)
        {
            if(rowId != 0)
            {   
                cout << rowId << "  ";
                PrintRow(rowId, playerPos);
            }
            else
            {
                cout << "  ";
                for(int colId=1; colId <= m_size; ++colId)
                    cout << "   " << colId;
            }
            cout << endl;
        }
    }

private:

    int m_size;

    // Horizontal bricks
    vector<bool> hBricks;

    int GetHBrickIndex(int colId, int rowIdBelow)
    {
        return (rowIdBelow*m_size + (colId-1));
    }

    bool IsHBrickBelow(int rowId, int colId)
    {
        return IsHBrickAbove(rowId-1, colId);
    }

    bool IsHBrickAbove(int rowId, int colId)
    {
        return hBricks[GetHBrickIndex(colId, rowId)];
    }

    // Vertical bricks
    vector<bool> vBricks;

    int GetVBrickIndex(int rowId, int leftColId)
    {
        return ((rowId-1)*(m_size+1) + leftColId);
    }

    bool IsVBrickToLeft(int rowId, int colId)
    {
        return IsVBrickToRight(rowId, colId-1);
    }

    bool IsVBrickToRight(int rowId, int colId)
    {
        return vBricks[GetVBrickIndex(rowId, colId)];
    }

    void PrintRow(int rowId, const Position& playerPos)
    {
        for(int colId=1; colId <= m_size; ++colId)
        {
            // Firstly draw left side vertical wall if present
            cout << (IsVBrickToLeft(rowId, colId) ? '|' : ' ');
           
            bool isPlayerPresent = (playerPos.GetRowId() == rowId) &&
                (playerPos.GetColId() == colId);
            char c = (IsHBrickBelow(rowId, colId) ? '_' : ' ');
            string str = {c, (isPlayerPresent ? 'X' : c), c};
            cout << str;

            // Draw right side border for right-most column
            if(colId == m_size)
                cout << (IsVBrickToRight(rowId, colId) ? '|' : ' ');
        }
    }    
};

bool SolveMazeHelper(Maze& maze, const Position& startPos, const Position& prevPos, vector<Position>& triedLocations)
{
    if(maze.CanUserExit(startPos))
    {
        maze.Print(startPos);
        return true;
    }
    else
    {
        // Choose
        triedLocations.push_back(startPos);

        // Explore
        auto candidatePosVec = maze.GetCandidatePositions(startPos);
        for(auto candidatePos : candidatePosVec)
        {
            if(std::find(triedLocations.begin(), triedLocations.end(), candidatePos) == triedLocations.end())
            {
                if(SolveMazeHelper(maze, candidatePos, startPos, triedLocations))
                {
                    maze.Print(startPos);
                    return true;
                }
            }
        }

        // Backtrack
        auto iter = std::find(triedLocations.begin(), triedLocations.end(), startPos);
        if(iter != triedLocations.end())
            triedLocations.erase(iter);
    }

    return false;
}

void SolveMaze(Maze& maze, Position startPos)
{
    vector<Position> triedLocations;
    SolveMazeHelper(maze, startPos, startPos, triedLocations);
}

int main()
{
    Maze maze(7);
    //maze.AddHDoor(4, true);
    //maze.AddHDoor(1, false);
    maze.AddVDoor(5, true);
    //maze.AddVDoor(4, false);

    unordered_map<int, vector<int>> vBricksRowIdToLeftColId =
    {
        {1, {1, 4}},
        {2, {2, 5}},
        {3, {1, 3, 6}},
        {4, {1, 4, 6}},
        {5, {1, 2, 3, 4, 5}},
        {6, {2, 4, 6}},
        {7, {1, 5}},
    };

    for(const auto& iter : vBricksRowIdToLeftColId)
        for(const auto& colIter : iter.second)
            maze.AddVBrick(iter.first, colIter);

    unordered_map<int, vector<int>> hBricksColIdToRowIdBelow =
    {
        {2, {2, 4}},
        {3, {1, 3, 4, 6}},
        {4, {1, 2, 6}},
        {5, {2, 3, 5}},
        {6, {1, 4, 6}},
        {7, {1}},
    };

    for(const auto& iter : hBricksColIdToRowIdBelow)
        for(const auto& rowIter : iter.second)
            maze.AddHBrick(iter.first, rowIter);

    SolveMaze(maze, {1,7});
}