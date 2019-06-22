//https://www.hackerrank.com/challenges/coin-on-the-table/problem

#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

int dp[52][52][1002];
map < char, int > mp;
int N, M;

int MIN(int a, int b, int c, int d)
{
    return min(min(a, b), min(c, d));
}

int findAns(vector < string > &board, int i, int j, int k)
{
    if(i < 0 || i >= N || j < 0 || j >= M)
        return INF;
    if(board[i][j] == '*')
        return 0;
    if(k == 0)
        return INF;
    if(dp[i][j][k] != -1)
        return dp[i][j][k];
    
    int ans;

    int dir = mp[board[i][j]];

    if(dir == 0)
    {
        ans = MIN(findAns(board, i-1, j, k-1), 1 + findAns(board, i+1, j, k-1), 1 + findAns(board, i, j-1, k-1), 1 + findAns(board, i, j+1, k-1) );
    } 
    else if(dir == 1)
    {
        ans = MIN(1 + findAns(board, i-1, j, k-1), 1 + findAns(board, i+1, j, k-1), 1 + findAns(board, i, j-1, k-1), findAns(board, i, j+1, k-1) );
    } 
    else if(dir == 2)
    {
        ans = MIN(1 + findAns(board, i-1, j, k-1), findAns(board, i+1, j, k-1), 1 + findAns(board, i, j-1, k-1), 1 + findAns(board, i, j+1, k-1) );
    } 
    else if(dir == 3)
    {
        ans = MIN(1 + findAns(board, i-1, j, k-1), 1 + findAns(board, i+1, j, k-1), findAns(board, i, j-1, k-1), 1 + findAns(board, i, j+1, k-1) );
    } 
    
    return dp[i][j][k] = ans;
}

int coinOnTheTable(int m, int k, vector<string> board) 
{
    N = board.size();
    M = board[0].size();

    int star_row, star_col;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if(board[i][j] == '*')
            {
                star_row = i;
                star_col = j;
            }
        }
    }
    if(k < (star_row + star_col))
        return -1;
 
    memset(dp, -1, sizeof(dp));

    mp['U'] = 0;
    mp['R'] = 1;
    mp['D'] = 2;
    mp['L'] = 3;

    return findAns(board, 0, 0, k);
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<string> board(n);

    for (int i = 0; i < n; i++) 
        cin >> board[i];

    int result = coinOnTheTable(m, k, board);

    cout << result << "\n";

    return 0;
}
