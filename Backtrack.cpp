#include<bits/stdc++.h>
using namespace std;
#define MAX 10

int n, cnt;

int dirX[] = {0, 1, 0, -1};
int dirY[] = {1, 0, -1, 0};

bool canPlace(int board[MAX][MAX], int row, int col, int move)
{
    if(row < 0 || row > n-1 || col < 0 || col > n-1 || board[row][col] == 1)
        return false;

    if(row == 0 && col == 0)
        return true;
    if(row == 0 && col == n-1)
        return true;
    if(row == n-1 && col == 0)
        return true;
    if(row == n-1 && col == n-1)
    {
        if(move != n*n-1)
            return false;
        return true;
    }
        
    if(row == 0)
    {
        if(board[row][col-1] == 0 && board[row][col+1] == 0)
            return false;
        else
            return true;
    }
    if(row == n-1)
    {
        if(board[row][col-1] == 0 && board[row][col+1] == 0)
            return false;
        else
            return true;
    }
    if(col == 0)
    {
        if(board[row-1][col] == 0 && board[row+1][col] == 0)
            return false;
        else
            return true;
    }
    if(col == n-1)
    {
        if(board[row-1][col] == 0 && board[row+1][col] == 0)
            return false;
        else
            return true;
    }
    
    if(board[row-1][col] == 1 && board[row+1][col] == 1 && board[row][col-1] == 0 && board[row][col+1] == 0)
        return false;
    if(board[row][col-1] == 1 && board[row][col+1] == 1 && board[row-1][col] == 0 && board[row+1][col] == 0)
        return false;
    
    return true;
}

void solveBoard(int board[MAX][MAX], int row, int col, int move)
{
    if(move == n*n)
    {
        cnt++;
        return;
    }

    for(int i = 0; i < 4; i++)
    {
        row += dirX[i], col += dirY[i];
        if(canPlace(board, row, col, move))
        {
            board[row][col] = 1;
            solveBoard(board, row, col, move+1);
            board[row][col] = 0; //backtrack
        }  
        row -= dirX[i], col -= dirY[i]; //backtrack
    }
}

int main()
{
    cin >> n;
    
    cnt = 0;
    
    int board[MAX][MAX] = {0};

    board[0][0] = 1;
    
    solveBoard(board, 0, 0, 1);
    
    cout << cnt << endl;
    
    return 0;
}
