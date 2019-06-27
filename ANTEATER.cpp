#include <bits/stdc++.h>
using namespace std;

int CountAntsMeet(int R, int C, vector<string> &board) 
{
    vector < int > pos[R*C];

    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {
            if(board[i][j] == 'U' || board[i][j] == 'D' || board[i][j] == 'L' || board[i][j] == 'R')
            {
                pos[i*C + j].push_back(1);
            }
        }
    }
    
    int p, q, temp;

    for(int i = 0; i < R; i++)
    {
        for(int j = 0; j < C; j++)
        {        
            p = i, q = j, temp = 2;
            if(board[i][j] == 'U')                
            {
                p = p-1;
                while(p >= 0 && p < R && q >= 0 && q < C && board[p][q] != '#')
                {
                    pos[p*C + q].push_back(temp++);
                    p--;
                }
            } 
            else if(board[i][j] == 'R')
            {
                q = q + 1;
                while(p >= 0 && p < R && q >= 0 && q < C && board[p][q] != '#')
                {
                    pos[p*C + q].push_back(temp++);
                    q++;
                }
            } 
            else if(board[i][j] == 'D')
            {
                p = p+1;
                while(p >= 0 && p < R && q >= 0 && q < C && board[p][q] != '#')
                {
                    pos[p*C + q].push_back(temp++);
                    p++;
                }
            } 
            else if(board[i][j] == 'L')
            {
                q = q-1;
                while(p >= 0 && p < R && q >= 0 && q < C && board[p][q] != '#')
                {
                    pos[p*C + q].push_back(temp++);
                    q--;
                }
            }  
        }
    }

    int res = 0, cnt;

    for(int i = 0; i < R*C; i++)
    {
        sort(pos[i].begin(), pos[i].end());
        
        for(int j = 1; j < pos[i].size(); j++)
        {
            cnt = 1;
            while(j != pos[i].size() && pos[i][j] == pos[i][j-1])
            {
                cnt++;
                j++;
            }
            res += ((cnt)*(cnt-1))/2;
        } 
    }

    return res;
}

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int R, C;
        cin >> R >> C;
        vector<string> board(R);

        for (int i = 0; i < R; i++) 
            cin >> board[i];

        cout << CountAntsMeet(R, C, board) << endl;
    }
    
    return 0;
}